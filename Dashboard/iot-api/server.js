'use strict'

const debug = require('debug')('iot:api')
const http = require('http')
const express = require('express')
const asyncify = require('express-asyncify')
const createAgent = require('iot-agent')

const api = require('./api')

const port = process.env.PORT || 3000
const app = asyncify(express())
const server = http.createServer(app)

app.use('/api', api)

app.use((err, req, res, next)=>
{
    debug(`Error: ${err.message}`)

    if (err.message.match(/not found/)) {
        return res.status(404).send({error: err.message})
    }

    res.status(500).send({error: err.message})
})

server.listen(port, ()=>{
    console.log(`El servidor esta corriendo en el puerto ${port}`)
    const agent =  createAgent({name: "Agente1"})
    agent.start()
    agent.on('connected')
})