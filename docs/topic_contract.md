# Topic Contracts (initial draft)

- `sensor.raw`  
  - Payload: `"<name>:<float_value>"`  
  - Rate: 20–200 Hz depending on scheduler setting.  
  - Consumer: perception stage.

- `control.cmd`  
  - Payload: ASCII float effort.  
  - Rate: matches upstream sensor; actuator consumes latest only.

Add new topics by extending this file with schema, units, and expected rate. Keep payloads backward compatible or versioned.
