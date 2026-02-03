#include <nodepp/nodepp.h>
#include <nodepp/test.h>

using namespace nodepp;

#include "enigma.h"

namespace TEST { namespace ENIGMA {

    void TEST_RUNNER(){
        ptr_t<uint> totl = new uint(0);
        ptr_t<uint> done = new uint(0);
        ptr_t<uint> err  = new uint(0);
        ptr_t<uint> skp  = new uint(0);

        auto test = TEST_CREATE();

        TEST_ADD( test, "TEST 1 | engima -> encryption", [](){
            try {

                ptr_t<uchar> rot ({ 0, 0, 0 });
                string_t msg = "hello world";

                if( regex::test( "2C6EEOCCF3R", encrypt( msg, rot ), true ) )
                  { TEST_DONE(); } else 
                  { TEST_FAIL(); }
                
            } catch ( ... ) { TEST_FAIL(); }
        });

        TEST_ADD( test, "TEST 2 | engima -> encryption", [](){
            try {

                ptr_t<uchar> rot ({ 22, 10, 30 });
                string_t msg = "Nodepp";

                if( regex::test( "JBRO3I", encrypt( msg, rot ), true ) )
                  { TEST_DONE(); } else 
                  { TEST_FAIL(); }
                
            } catch ( ... ) { TEST_FAIL(); }
        });

        TEST_ADD( test, "TEST 3 | engima -> encryption", [](){
            try {

                ptr_t<uchar> rot ({ 10, 20, 30 });
                string_t msg = "Enigma Machine";

                if( regex::test( "YGZNCRGVX1ELV4", encrypt( msg, rot ), true ) )
                  { TEST_DONE(); } else 
                  { TEST_FAIL(); }
                
            } catch ( ... ) { TEST_FAIL(); }
        });



        TEST_ADD( test, "TEST 1 | engima -> decryption", [](){
            try {

                ptr_t<uchar> rot ({ 0, 0, 0 });
                string_t msg = "2C6EEOCCF3R";

                if( regex::test( "hello world", encrypt( msg, rot ), true ) )
                  { TEST_DONE(); } else 
                  { TEST_FAIL(); }
                
            } catch ( ... ) { TEST_FAIL(); }
        });

        TEST_ADD( test, "TEST 2 | engima -> decryption", [](){
            try {

                ptr_t<uchar> rot ({ 22, 10, 30 });
                string_t msg = "JBRO3I";

                if( regex::test( "Nodepp", encrypt( msg, rot ), true ) )
                  { TEST_DONE(); } else 
                  { TEST_FAIL(); }
                
            } catch ( ... ) { TEST_FAIL(); }
        });

        TEST_ADD( test, "TEST 3 | engima -> decryption", [](){
            try {

                ptr_t<uchar> rot ({ 10, 20, 30 });
                string_t msg = "YGZNCRGVX1ELV4";

                if( regex::test( "Enigma Machine", encrypt( msg, rot ), true ) )
                  { TEST_DONE(); } else 
                  { TEST_FAIL(); }
                
            } catch ( ... ) { TEST_FAIL(); }
        });

        test.onClose.once([=](){
            console::log("\nRESULT | total:", *totl, "| passed:", *done, "| error:", *err, "| skipped:", *skp );
        });

        test.onDone([=](){ (*done)++; (*totl)++; });
        test.onFail([=](){ (*err)++;  (*totl)++; });
        test.onSkip([=](){ (*skp)++;  (*totl)++; });

        TEST_AWAIT( test );

    }

}}

void onMain() { TEST::ENIGMA::TEST_RUNNER(); }