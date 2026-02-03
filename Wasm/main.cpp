#include <nodepp/nodepp.h>
#include <nodepp/bind.h>

using namespace nodepp;

#include "enigma.h"

EM_STRING get_enigma_data( EM_STRING data, uchar rot0, uchar rot1, uchar rot2 ){
    return encrypt( data.c_str(), ptr_t<uchar>({ rot0, rot1, rot2 }) ).get();
}

void onMain(){ }

BIND( MODULE ){
    BIND_ADD( "encrypt", &get_enigma_data )
}

