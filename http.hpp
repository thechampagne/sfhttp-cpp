/*
 * zlib License
 * 
 * (C) 2032 XXIV
 * 
 * This software is provided *as-is*, without any express or implied
 * warranty.  In no event will the authors be held liable for any damages
 * arising from the use of this software.
 * 
 * Permission is granted to anyone to use this software for any purpose,
 * including commercial applications, and to alter it and redistribute it
 * freely, subject to the following restrictions:
 * 
 * 1. The origin of this software must not be misrepresented; you must not
 *    claim that you wrote the original software. If you use this software
 *    in a product, an acknowledgment in the product documentation would be
 *    appreciated but is not required.
 * 2. Altered source versions must be plainly marked as such, and must not be
 *    misrepresented as being the original software.
 * 3. This notice may not be removed or altered from any source distribution.
 */
#ifndef __SFHTTP_HPP__
#define __SFHTTP_HPP__

namespace http {
  #include "http.h"

  class Client {
    http_t * _http;
    Client() {}
    public:
      enum Status {
        PENDING,
        COMPLETED,
        FAILED,
      };
    Status status;
    int status_code;
    char
    const * reason_phrase;
    char
    const * content_type;
    size_t response_size;
    void * response_data;

    Client Get(char
      const * url, void * memctx) {
      Client client;
      auto http = http_get(url, memctx);
      client._http = http;
      return client;
    }

    Client Post(char
      const * url, void
      const * data, size_t size, void * memctx) {
      Client client;
      auto http = http_post(url, data, size, memctx);
      client._http = http;
      return client;
    }

    Status Process() {
        auto result = http_process(this -> _http);
        this -> status = static_cast < Status > (this -> _http -> status);
        this -> status_code = this -> _http -> status_code;
        this -> reason_phrase = this -> _http -> reason_phrase;
        this -> content_type = this -> _http -> content_type;
        this -> response_size = this -> _http -> response_size;
        this -> response_data = this -> _http -> response_data;
        return static_cast < Status > (result);
      }

      ~Client() {
        http_release(this -> _http);
      }
  };
}

#endif // __SFHTTP_HPP__
