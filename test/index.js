/**
 * Copyright (c) 2012-2015 Qeemo Ltd. All Rights Reserved.
 */
/**
 * User: Kurten
 * Date: 2015-12-21
 * Time: 15:56
 * Version: 1.0
 * Description:
 */
'use strict';
const bindings = require('../');
const assert = require('assert');

console.log(bindings.hash('hello1', 0));

console.log(bindings.hash64('foo', 0, true));

const buf = bindings.hash_bytes('foo', 0, true);
console.log(buf, buf.toString(), buf.toString('base64'), buf.toString('hex'));