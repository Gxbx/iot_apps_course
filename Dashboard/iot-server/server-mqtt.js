'use strict'

const mosca = require('mosca')
const redis = require('redis')
const dbConnect = require('iot-db')

let backend = {
    type: 'redis',
    redis: redis,
    return_buffer: true
}
let settings = {
    port: 1883,
    backend: backend
}

const server = new mosca.Server(settings)
const clients = new Map()
let Agent

server.on('clientConnected', (client) =>
{
    clients.set(client.id, null)    
})

server.on('clientDisconnected', async (client) =>
{   
    const agent = clients.get(client.id)
    if (agent) {
        agent.connected = false
        await agent.save()
            .catch(handleError)
        
        clients.delete(client.id)

        server.publish({ topic: 'agent/disconnected', payload: JSON.stringify({agent: agent.uuid}) })
    }
})

server.on('published', async(packet, client) =>
{
    switch (packet.topic)
    {
        case 'agent/connected':
            break
        case 'agent/disconnected':
            break
        case 'agent/message':
            const payload = packet.payload

            if (payload) {
                let agent =  await Agent.findOne({uuid: payload.agent.uuid})
                    .catch(handleError)
                if (!agent) {
                    agent = new Agent(payload.agent)
                }

                agent.values.push({memory: payload.value, timestamp: payload.timestamp})

                agent.connected = true

                await agent.save()
                    .catch(handleError)
                if (!clients.get(client.id))
                {
                    clients.set(client.id, agent)
                    server.publish({topic: 'agent/connected', payload: JSON.stringify({agent: agent.uuid})})
                }
                
            }
            break
    }
})

server.on('ready', async() =>{
    const db = await dbConnect().catch(handleError)
    Agent = db.Agent
    console.log('MQTT Server esta corriendo .....')
})

server.on('error', handleError)

function handleError (err){
    console.error(`Un error ha ocurrido: ${err.message}`)
}
function handleFatalError (err){
    console.error(`Un error fatal ha detenido el programa :'(): ${err.message}`)
    process.exit(1)
}
