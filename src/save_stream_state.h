//
//  save_stream_state.h
//
//  Created by Paul Ross on 14/09/2018.
//  Copyright © 2018 Paul Ross. All rights reserved.
//

#ifndef PYTHONCPPHOMOGENEOUSCONTAINERS_SAVE_STREAM_STATE_H
#define PYTHONCPPHOMOGENEOUSCONTAINERS_SAVE_STREAM_STATE_H

#include <iostream>
#include <iomanip>

class StreamFormatState {
public:
    StreamFormatState(std::basic_ios<char> &stream) : _pStream(&stream), _ff(stream.flags()), _fill(stream.fill()) {}
    ~StreamFormatState() {
        if (_pStream) {
            _pStream->flags(_ff);
            _pStream->fill(_fill);
        }
    }
private:
    std::basic_ios<char> *_pStream;
    std::ios_base::fmtflags _ff;
    char _fill;
};

#endif //PYTHONCPPHOMOGENEOUSCONTAINERS_SAVE_STREAM_STATE_H
