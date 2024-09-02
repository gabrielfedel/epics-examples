# ASG example

The following exaple shows how to use ASG to protect PVs

## How to use:

Run first IOC with a PV `test1` belonging to `ALLOW-MANUAL` access security group:

```
iocsh st.cmd
```

Run second IOC with a PV `allow:manual`

```
iocsh st_ctrl.cmd
```

When `allow:manual.VAL` is `1`, then write action is possible from any host.

When `allow:manual.VAL` is `0`, then write action is possible only from specified hosts in `HAG(labvm)`.

When IOC providing `allow:manual` is stopped, then the `allow:manual:cpy` in first IOC is forced to 0 and write action is allowed from every host.

