'use strict'

const mongoose = require('mongoose')
const agentSchema = require('./agent')

//Esta libreria es para hacer Promises personalizadas
mongoose.Promise = require('bluebird') 

//Hacer la conexión y plasmar los schemas en la bd
module.exports = async function connect (dbUrl = 'mongodb://localhost:27017/iot')
{ 
    let conn = await mongoose.createConnection(dbUrl, {useMongoClient: true})
    return{
        Agent: conn.model('Agent', agentSchema)
    }
}
