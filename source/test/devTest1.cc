  /// \file devTest.cc
/*
 *
 * devTest1.cc main file
 * Creation date : jeu. juin 6 2013
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
 */


#include "RawCfgParser.hh"
#include "CfgParser.hh"
#include "ParserStatus.hh"
#include "StrOp.hh"

#include <string>
#include <locale>

using namespace std;
using namespace cfgparser;




int main( int argc , char *argv[] ) {

	// grab the file name at runtime in the first argument
	if( argc != 2 ) {
		cerr << "example1 need exactly one argument which is a *.cfg configuration file." << endl;
		exit( 1 );
	}

	string fileName( argv[1] );

	cout << "Declaring an instance of RawCfgParser" << endl;
	RawCfgParser *parser = new RawCfgParser();

	string sectionName = "mySection";
	string keyName = "anInteger";

	ifstream *file = new ifstream( fileName.c_str() );
	CFGPARSER_THROW_RESULT_IF( CFGPARSER_SUCCESS() , != , parser->Read( file ) );


	// Split test
	string str("dflg ieh edcl kefbn ");
	vector<string> splitStr = Split( str , 'e'  );

	cout << "'";
	for( unsigned int i=0 ; i<splitStr.size() ; i++ )
		cout << splitStr.at(i) << endl;
	cout << "'" << endl;


	// other Split test
	splitStr.clear();
	str = "14:85:4521:856";
	splitStr = Split( str , ':' );

	cout << "'";
	for( unsigned int i=0 ; i<splitStr.size() ; i++ )
		cout << splitStr.at(i) << endl;
	cout << "'" << endl;

	cout << "I'm a " << Split( "bibou,babouba,endl", ',' ).at(0) << endl;


	// ToLower test
	str = "I'M A BABOON!";
	cout << "normal : " << str << endl;
	cout << "to lower : " << ToLower( str ) << endl;

	// RStrTrim test
	string trimTest = "   bibou   ";
	cout << "before trim : '" << trimTest << "'" << endl;
	RStrTrim( &trimTest );
	cout << "after trim : '" << trimTest << "'" << endl;

	cout << "---------------------------------" << endl;

	const Section *sec = parser->GetSection( sectionName );
	const Section *defaultSec = parser->GetDefaultSection();

	if( sec == 0 )
		cout << "no section named "+sectionName << endl;
	else {

		cout << "section : " << sec->GetName() << endl;
		int vInt = 0;
		string vString;
		string aMultiLineKey = "aMultiLineValue";
		string aMultiLineValue = "";
		CFGPARSER_THROW_RESULT_IF( CFGPARSER_SUCCESS() , != , sec->GetValue( keyName , &vInt ) );
		CFGPARSER_THROW_RESULT_IF( CFGPARSER_SUCCESS() , != , sec->GetValue( keyName , &vString ) );
		CFGPARSER_THROW_RESULT_IF( CFGPARSER_SUCCESS() , != , sec->GetValue( aMultiLineKey , &aMultiLineValue ) );


		cout << "my int val : " << vInt << endl;
		cout << "my string val : " << vString << endl;
		cout << "aMultiLineValue : " << aMultiLineValue << endl;


	}

	if( defaultSec == 0 ) {
		cout << "default section not found!" << endl;
	}
	else {
		int anImportantInt = 0;
		CFGPARSER_THROW_RESULT_IF( CFGPARSER_SUCCESS() , != , defaultSec->GetValue( "anImportantInt" , &anImportantInt ) );
	}


	// CfgParser test
	CfgParser *cfgParser = new CfgParser();

	CFGPARSER_THROW_RESULT_IF( CFGPARSER_SUCCESS() , != , cfgParser->Read( fileName ) );

	string myOptionName = "myOption";
	string myOptionValue;

	CFGPARSER_THROW_RESULT_IF( CFGPARSER_SUCCESS() , != , cfgParser->GetValue( sectionName , myOptionName , &myOptionValue , true ) );
	cout << "myOptionValue : " << myOptionValue << endl;


	CFGPARSER_THROW_RESULT_IF( CFGPARSER_SUCCESS() , != , cfgParser->GetValue( sectionName , myOptionName , &myOptionValue , false ) );
	cout << "myOptionValue : " << myOptionValue << endl;

	delete cfgParser;
	delete parser;
	delete file;
	return 0;
}
