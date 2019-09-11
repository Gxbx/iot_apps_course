'use strict'

const mongoose = require('mongoose')
const Schema = mongoose.Schema

const agentSchema = new Schema
({
    uuid: String,
    name: String,
    hostname: String,
    connected: Boolean,
    vlaues: [{memory: Object, timestamp: Date}]
})
module.exports = agentSchema