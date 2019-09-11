'use strict'

const debug = require('debug')('iot:api:api')
const express = require('express')
const asyncify = require('express-asyncify')
const dbConnect = require('iot-db')
const api = asyncify(express.Router())
let Agent

api.use('*', async (req, res, next) =>
{
    if (!Agent){
        const db = await dbConnect()
        Agent = db.Agent
    }
    next()
})
api.get('/agents', async (req, res) =>
{
    debug('peticion a el API Agentes')
    let agents = await Agent.find({ connected: true})
    res.send(agents)
})

api.get('/agent/:id', async (req, res, next) =>
{
    let id  = req.params.id
    if (!id) {
      return next(new Error('El id no es válido'))  
    }
    debug(`request al agente/${id}`)

    let agent = await Agent.findOne({uuid: id})

    if (!agent) {
        return next (new Error ('Agente no encontrado'))
    }

    res.send(agent.toObject())
})

module.exports = api