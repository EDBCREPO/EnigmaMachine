#include <nodepp/nodepp.h>
#include <express/http.h>
#include <nodepp/json.h>

using namespace nodepp;

#include "enigma.h"

void onMain(){

    auto app = express::http::add();

    app.GET([=]( express_http_t cli ){  if( !cli.search.empty() ){

        auto rot = ptr_t<uchar>( 3UL ); 
        auto obj = query::parse( cli.search );
        auto msg = url::normalize( obj["msg"] ).to_upper_case();

        string::parse( obj["rot"], "%u_%u_%u", &rot[0], &rot[1], &rot[2] );
        auto out = encrypt( msg, rot );

        cli.send( json::stringify( object_t({
            { "msg", out.empty() ? "" : out }
        })) );
        
    return; } });

    app.USE( express::http::file( "./www" ) );

    app.listen( "localhost", 8000, [=]( socket_t /*unused*/ ){
        console::log("server started at http://localhost:8000");
    });

}