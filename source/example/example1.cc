  /// \file example1.cc
/*
 *
 * example1.cc main file
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


#include "RawCfgParser.hh"
#include "CfgParser.hh"
#include "ParserStatus.hh"
#include "StrOp.hh"


#include <string>
#include <locale>
#include <cstdlib>

using namespace std;
using namespace cfgparser;



int main( int argc , char *argv[] ) {

	// grab the file name at runtime in the first argument
	if( argc != 2 ) {
		cerr << "example1 need exactly one argument which is a *.cfg configuration file." << endl;
		exit( 1 );
	}

	string fileName( argv[1] );


	// Use simple RawCfgParser to parse and write a configuration file.
	RawCfgParser *rawParser = new RawCfgParser();

	/*
	 * Four methods can be used to parse a cfg file:
	 *
	 * 1. By using a string for file name
	 * By using a ifstream standard file:
	 *    2. with a pointer
	 *    3. with a reference
	 * 4. By passing multiple file names in a vector string.
	 *
	 * !! Be careful with the last one. The kept values depends on
	 * the order you pass the cfg file string. The last file will
	 * keep the right values in case of overloaded options !!
	 *
	 * To check if there no error while reading, use status code.
	 * You can use macros or a simple check
	 *
	 */

	// Using a string and without any check
	rawParser->Read( fileName );

	rawParser->Clear();



	// Using a ifstream ( pointer or reference ) and using a simple check.
	ifstream *fileStream = new ifstream( fileName.c_str() );
	StatusCode st = rawParser->Read( fileStream );

	if( st != CFGPARSER_SUCCESS() ) {

		cout << "   File '" << fileName << "' got an error while reading.\n"
				"   The program has to terminate!" << endl;
		exit( 1 );
	}

	rawParser->Clear();



	// Using a string vector ( here only one file ) and CfgParser library macros.
	// Throw a CfgParserException if an error is found while parsing.
	StringCollection fileNames;
	fileNames.push_back( fileName );

	CFGPARSER_THROW_RESULT_IF( CFGPARSER_SUCCESS() , != , rawParser->Read( fileNames ) );

	rawParser->Clear();




	delete rawParser;

	return 0;
}




