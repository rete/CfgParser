  /// \file CfgParser.cc
/*
 *
 * CfgParser.cc source file template generated by fclass
 * Creation date : jeu. juin 6 2013
 *
 * This file is part of CfgParser libraries.
 *
 * CfgParser is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * CfgParser is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with CfgParser.  If not, see <http://www.gnu.org/licenses/>.
 *
 * @author : Eté Rémi
 * @version 0.1.0 13/08/2013
 * @copyright 2013 Eté Rémi
 *
 */


using namespace std;


#include "CfgParser.hh"



namespace cfgparser {


//---------------------------------------------------------------------------------------------------------------

	/****************************
	 * Public member functions
	 ****************************/

	ChainSection::ChainSection()
		: _sectionCollection( new SectionCollection() )
	{

	}

	ChainSection::~ChainSection()
	{
		_sectionCollection->clear();
		delete _sectionCollection;
	}

	string ChainSection::getValue( const std::string &option ) const
	{
		string value = "";
		for( auto i=0 ; i<_sectionCollection->size() ; i++ ) {

			try{
				value = _sectionCollection->at(i)->getValue<string>( option );
				return std::move( value );
			} catch ( CfgParserException &e ) {
				value = "";
				continue;
			}
		}
		return std::move( value );
	}


	StringCollection ChainSection::getOptions() const
	{
		StringCollection result;
		StringCollection seen;

		for( unsigned int i=0 ; i<_sectionCollection->size() ; i++ ) {

			auto optValMap = _sectionCollection->at(i)->getOptionValueMap();

			for( auto it = optValMap.begin() ; it != optValMap.end() ; it++ ) {

				if( std::find( seen.begin() , seen.end() , it->first ) == seen.end() ) {

					seen.push_back( it->first );
					result.push_back( it->first );
				}
			}
		}

		return result;
	}


	bool ChainSection::hasOption( const std::string &opt ) const
	{
		return ( std::find_if( _sectionCollection->begin()
							, _sectionCollection->end()
							, [&] (Section *s) -> bool { return s->hasOption( opt ); } )
			!= _sectionCollection->end() );
	}


//-------------------------------------------------------------------------------------------------------------------------------

	/****************************
	 * Public member functions
	 ****************************/

	CfgParser::CfgParser()
		: RawCfgParser()
	{

	}

//---------------------------------------------------------------------------------------------------------------

	/****************************
	 * Private member functions
	 ****************************/

	StatusCode CfgParser::interpolate( const std::string &str , const ChainSection *chainSection , std::string *value ) const
	{
		string finalString = str;
		string tempString = str;

		size_t posOpen = 0;
		size_t posClose = 0;

		while( true ) {

			posOpen = finalString.find( "%(" , posOpen );

			if( posOpen > finalString.size() )
				break;

			posClose = finalString.find( ")s" , posOpen );

			if( posClose > finalString.size() )
				return CFGPARSER_INTERPOLATION_SYNTAX_ERROR("Interpolation error in string '"+ str +"' : missing ')s'");

			string opt = finalString.substr( posOpen+2 , posClose - (posOpen+2) );

			if( chainSection->hasOption( RawCfgParser::optionXForm( opt ) ) ) {
				string val;
				val = chainSection->getValue( opt );
				finalString.replace( posOpen , (posClose-posOpen)+2 , val );
			}
			else {
				return CFGPARSER_INTERPOLATION_MISSING_OPTION_ERROR("Interpolation error in string '"+ str +"' , KeyError: '"+ opt +"'");
			}
		}

		*value = finalString;

		return CFGPARSER_SUCCESS();
	}


}  //  end namespace cfgparser
