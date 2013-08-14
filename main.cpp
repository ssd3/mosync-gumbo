#include <MAUtil/Moblet.h>
#include <conprint.h>
#include "gumbo_header/gumbo.h"

using namespace MAUtil;

/**
 * A Moblet is a high-level class that defines the
 * behaviour of a MoSync program.
 */
class MyMoblet : public Moblet
{
public:
	/**
	 * Initialize the application in the constructor.
	 */
	MyMoblet()
	{
		printf("Gumbo - A pure-C HTML5 parser.\n");
		printf("Gumbo is an implementation of the HTML5 parsing algorithm implemented as a pure C99 library with no outside dependencies. It's designed to serve as a building block for other tools and libraries such as linters, validators, templating languages, and refactoring and analysis tools.\n\n");
		printf("Example: Finds the URLs of all links in the page.\n\n");

		GumboOutput* output = gumbo_parse("<html><body><p>Gumbo is an implementation of the <a href=\"http://link0.com\">HTML5 parsing algorithm</a>implemented as a pure C99 library with no outside dependencies.  <a href=\"http://link1.com\">Link 1</a>It's designed to serve as a <a href=\"http://link2.com\">Link 2</a>building block for other tools and libraries such as linters, validators, templating languages, and refactoring and analysis tools.</p></body></html>");
 	    search_for_links(output->root);
		gumbo_destroy_output(&kGumboDefaultOptions, output);
	}

	/**
	 * Called when a key is pressed.
	 */
	void keyPressEvent(int keyCode, int nativeCode)
	{
		if (MAK_BACK == keyCode || MAK_0 == keyCode)
		{
			// Call close to exit the application.
			close();
		}

		// Print the key character.
		printf("You typed: %c\n", keyCode);
	}

	/**
	 * Called when a key is released.
	 */
	void keyReleaseEvent(int keyCode, int nativeCode)
	{
	}

	/**
	 * Called when the screen is touched.
	 */
	void pointerPressEvent(MAPoint2d point)
	{
		// Print the x and y coordinate.
		printf("You touched: %i %i\n", point.x, point.y);
	}

	void search_for_links(GumboNode* node) {
	  if (node->type != GUMBO_NODE_ELEMENT) {
	    return;
	  }
	  GumboAttribute* href;
	  if (node->v.element.tag == GUMBO_TAG_A && (href = gumbo_get_attribute(&node->v.element.attributes, "href"))) {
		  printf("Href Value: %s\n", href->value);
	  }

	  GumboVector* children = &node->v.element.children;
	  for (int i = 0; i < children->length; ++i) {
	    search_for_links(static_cast<GumboNode*>(children->data[i]));
	  }
	}

};

/**
 * Entry point of the program. The MAMain function
 * needs to be declared as extern "C".
 */
extern "C" int MAMain()
{
	Moblet::run(new MyMoblet());
	return 0;
}




// Copyright 2013 Google Inc. All Rights Reserved.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
//
// Author: jdtang@google.com (Jonathan Tang)
//
// Finds the URLs of all links in the page.

//#include <stdlib.h>
//
//#include <fstream>
//#include <iostream>
//#include <string>
//
//#include "gumbo.h"
//
//static void search_for_links(GumboNode* node) {
//  if (node->type != GUMBO_NODE_ELEMENT) {
//    return;
//  }
//  GumboAttribute* href;
//  if (node->v.element.tag == GUMBO_TAG_A &&
//      (href = gumbo_get_attribute(&node->v.element.attributes, "href"))) {
//    std::cout << href->value << std::endl;
//  }
//
//  GumboVector* children = &node->v.element.children;
//  for (int i = 0; i < children->length; ++i) {
//    search_for_links(static_cast<GumboNode*>(children->data[i]));
//  }
//}
//
//int main(int argc, char** argv) {
//  if (argc != 2) {
//    std::cout << "Usage: find_links <html filename>.\n";
//    exit(EXIT_FAILURE);
//  }
//  const char* filename = argv[1];
//
//  std::ifstream in(filename, std::ios::in | std::ios::binary);
//  if (!in) {
//    std::cout << "File " << filename << " not found!\n";
//    exit(EXIT_FAILURE);
//  }
//
//  std::string contents;
//  in.seekg(0, std::ios::end);
//  contents.resize(in.tellg());
//  in.seekg(0, std::ios::beg);
//  in.read(&contents[0], contents.size());
//  in.close();
//
//  GumboOutput* output = gumbo_parse(contents.c_str());
//  search_for_links(output->root);
//  gumbo_destroy_output(&kGumboDefaultOptions, output);
//}
