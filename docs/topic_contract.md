# Topic Contracts (initial draft)

- `sensor.raw`  
  - Payload: `"<name>:<float_value>"`  
  - Rate: 20-200 Hz depending on scheduler setting.  
  - Consumer: perception stage.

- `control.cmd`  
  - Payload: ASCII float effort.  
  - Rate: matches upstream sensor; actuator consumes latest only.

- `health.heartbeat`  
  - Payload: `"ts_ms:<uint64>"` monotonic timestamp in milliseconds.  
  - Rate: 1 Hz nominal; consumers treat >3s silence as degraded health.

Add new topics by extending this file with schema, units, and expected rate. Keep payloads backward compatible or versioned.
