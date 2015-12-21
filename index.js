/**
 * Copyright (c) 2012-2015 Qeemo Ltd. All Rights Reserved.
 */
/**
 * User: Kurten
 * Date: 2015-12-21
 * Time: 15:53
 * Version: 1.0
 * Description:
 */
'use strict';

const bindings = require('bindings')('murmur3_lib');
/**
 * hash function
 * @param  {String} str source string
 * @return {int}        hashed number
 */
exports.hash = function (str) {
    let seed = 0;
    if (arguments.length === 2) {
        seed = parseInt(arguments[1], 10);
    }
    if (isNaN(seed)) {
        throw new Error('seed must be number');
    }

    return bindings.hash(str, seed);
};
/**
 * hash64 function
 * @param  {String}  str       source string
 * @param  {int}     seed      seed for hash
 * @param  {boolean} x64arch   x64 true or false(default true) 
 * @return {array}             hashed number array
 */
exports.hash64 = function (str) {
    let seed = 0;
    if (arguments.length > 1) {
        seed = parseInt(arguments[1], 10);
    }
    if (isNaN(seed)) {
        throw new Error('seed must be number');
    }
    let x64arch = true;
    if (arguments.length > 2) {
        x64arch = arguments[2];
    }
    if (typeof x64arch !== 'boolean') {
        throw new Error('x64arch must be boolean');
    }

    return bindings.hash64(str, seed, x64arch);
};
/**
 * like hash64 function but return 16 length buffer 
 * @param  {String}  str       source string
 * @param  {int}     seed      seed for hash
 * @param  {boolean} x64arch   x64 true or false(default true) 
 * @return {Buffer}            bytes
 */
exports.hash_bytes = function (str) {
    let seed = 0;
    if (arguments.length > 1) {
        seed = parseInt(arguments[1], 10);
    }
    if (isNaN(seed)) {
        throw new Error('seed must be number');
    }
    let x64arch = true;
    if (arguments.length > 2) {
        x64arch = arguments[2];
    }
    if (typeof x64arch !== 'boolean') {
        throw new Error('x64arch must be boolean');
    }

    return bindings.hash_bytes(str, seed, x64arch);
};
