A murmur3 library for NodeJS.

Distributed under terms of the MIT license.

see test/index.js for examples
or 
run `npm test`

# API
`murmur3.`
  * `hash(str)` - return int
    * `str` - [MUST] - the source string.
    * `seed` - [OPTIONAL] - seed for hash default 0.
  * `hash64(str)` - return array
    * `str` - [MUST] - the source string.
    * `seed` - [OPTIONAL] - seed for hash default 0.
    * `x64arch` - [OPTIONAL] - is x86(false) or x64(true) default x64(true).
  * `hash_bytes(str)` - return Buffer
    * `str` - [MUST] - the source string.
    * `seed` - [OPTIONAL] - seed for hash default 0.
    * `x64arch` - [OPTIONAL] - is x86(false) or x64(true) default x64(true).

# Note
hash64 maybe not work expected because of int64 in javascript