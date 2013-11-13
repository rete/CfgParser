  /// \file cfgparser_getvalue.cc
/*
 *
 * cfgparser_getvalue.cc main file
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
 * Parse a cfg file and extract a value
 * with an interpolation.
 *
 */


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
	if( argc != 4 ) {

		cerr << "Usage: cfgparser_getvalue *.cfg sectionName optionName" << endl;
		cerr << "cfgparser_getvalue need exactly 3 arguments." << endl;
		exit( 1 );
	}

	string fileName( argv[1] );
	string sectionName( argv[2] );
	string optionName( argv[3] );
	string value;

	CfgParser *parser = new CfgParser();

	parser->read( fileName );

	// print the value
	cout << parser->getValue<string>( sectionName , optionName , false ) << endl;

	delete parser;

	return 0;
}




