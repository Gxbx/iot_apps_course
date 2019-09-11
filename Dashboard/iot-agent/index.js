'use strict'

const debug =  require('debug')('iot:agent')
const os = require('os')
const mqtt = require('mqtt')
const uuid = require('uuid')
const defaults = require('defaults')
const EventEmitter = require('events')

const options = {
    name: 'IoTMQTTBroker',
    interval: 1000,
    mqtt: {
        host: 'mqtt://192.168.1.197',
        user: 'Gabriel',
        pass: '12345678'
    }
}

class IoTAgent extends EventEmitter 
{
   constructor(opts)
   {
       super()
       this.options = defaults(opts, options)
   }
   
   start()
   {
       if (!this.started)
       {
           const opts = this.options
           const client = mqtt.connect(opts.mqtt.host)
           this.started =  true

           client.on('connect', ()=> {
               const agentID  = uuid.v4()
               this.emit('connected',agentID)

               setInterval(()=>{
                   let message = {
                      agent: {
                          uuid: agentID,
                          name: opts.name,
                          hostname: os.hostname() || 'localhost',
                          pid: process.pid
                      },
                      value: process.memoryUsage(),
                      timestamp:  new Date()
                   }
                   debug ('Enviando...', message)
                   client.publish('esp32/massege/output', JSON.stringify(message))
                   this.emit('message', message)
               }, opts.interval)
           })
           client.on('error', ()=>
           {
               this.started = false
           })
       }
   }
}


