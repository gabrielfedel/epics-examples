# calc

## Counter

Demonstrates a simple counter, increasing once the record is triggered.

## Example last value

Demonstrates the possibility to monitor the change of value using .LA field.

### How to test
``` 
$ iocsh st_last_value.cmd

> dbpf test::Temperature 10
DBF_DOUBLE:         10
> dbpf test::Temperature 8
DBF_DOUBLE:         8
> dbpf test::Temperature 12
DBF_DOUBLE:         12
> dbpf test::Temperature 10
DBF_DOUBLE:         10
> dbpf test::Temperature 10
DBF_DOUBLE:         10
> dbpf test::Temperature 10
DBF_DOUBLE:         10
> dbpf test::Temperature 10
DBF_DOUBLE:         10
>

```

### Monitor
```
$ camonitor test::Temperature test::TemperatureChange
test::Temperature              <undefined> 0 UDF NO_ALARM
test::TemperatureChange        2026-03-18 13:40:49.040436 0
test::Temperature              2026-03-18 13:41:14.014335 10
test::TemperatureChange        2026-03-18 13:41:14.014584 10
test::Temperature              2026-03-18 13:41:16.027830 8
test::TemperatureChange        2026-03-18 13:41:16.027923 -2
test::Temperature              2026-03-18 13:41:18.267505 12
test::TemperatureChange        2026-03-18 13:41:18.267719 4
test::Temperature              2026-03-18 13:41:20.418632 10
test::TemperatureChange        2026-03-18 13:41:20.418796 -2
test::Temperature              2026-03-18 13:41:21.384354 10
test::TemperatureChange        2026-03-18 13:41:21.384527 0
test::Temperature              2026-03-18 13:41:22.064006 10
test::Temperature              2026-03-18 13:41:29.486182 10

```