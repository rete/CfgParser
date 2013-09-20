  /// \file example2.cc
/*
 *
 * example2.cc main file
 * Creation date : jeu. aout 31 2013
 *
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
 *
 *
 *
 * DESCRIPTION:
 *
 * This example shows how the base class RawCfgParser
 * can be used to parse and write a simple configuration
 * file with ini format.
 *
 *
 */


#include "CfgParser.hh"
#include "ParserStatus.hh"
#include "Section.hh"
#include "StrOp.hh"


#include <string>
#include <locale>
#include <cstdlib>

using namespace std;
using namespace cfgparser;



int main( int argc , char *argv[] ) {

	// grab the file name at runtime in the first argument
	if( argc != 2 ) {
		cerr << "example2 needs exactly one argument which is a *.cfg configuration file."
				"This file will be created. If the given one already exists, it will be overwritten." << endl;
		exit( 1 );
	}

	string fileName( argv[1] );


	// Use RawCfgParser to parse and write a configuration file.
	RawCfgParser *rawParser = new RawCfgParser();

	cout << "Creating a section called \"BasicSection\"" << endl;
	string basicSectionName("BasicSection");
	CFGPARSER_THROW_RESULT_IF( CFGPARSER_SUCCESS() , != , rawParser->CreateSection( basicSectionName ) );

	if( rawParser->HasSection( basicSectionName ) ) {
		cout << basicSectionName + " has been created!" << endl;
	}

	cout << "Setting an option called \"anInteger\" to 42" << endl;
	CFGPARSER_THROW_RESULT_IF( CFGPARSER_SUCCESS() , != , rawParser->SetValue( basicSectionName , "anInteger" , 42 ) );

	cout << "Printing the created section :" << endl;
	const Section *basicSection = rawParser->GetSection( basicSectionName );
	basicSection->Print();

	cout << "Generating cfg file with name \"" + fileName + "\"" << endl;
	rawParser->Write( fileName );

	delete rawParser;

	return 0;
}




