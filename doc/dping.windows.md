# dping

## About
`dping` is a tool for distributed pinging of specified destination host. This tool works almost the same as Windows and Linux built-in tools, but all network operations are going from different hosts in internet.

## Usage

```
Usage: dping --help
    --version
    --list-country [-v] [--debug]
    --list-asn code [-v] [--debug]
    --country code [-n probes] [-w timeout] [-t] [-v] {target_name}
    --asn id [-n probes] [-w timeout] [-t] [-v] {target_name}

Options:
    {target_name}  Destination host IP or domain name.

    --help          Display this help.
    --version       Display detailed program version, copyright notices.
    --list-country  List available countries.
    --list-asn code List ASNs for specified 2 letter country code.
    --country code  Specify source addresses 2 letter country code
                    (ISO 3166-1 alpha-2).
    --asn id        Use source addresses from specified ASN.
                    (autonomous system number) network.
    -n probes       Probes limit: number of hosts to make requests from.
                    This option has an alias: --probes probes
    -w timeout      Timeout in milliseconds to wait for single ping.
    -t              Ping the specified host until stopped.
                    To see statistics and continue - type Control-Break;
                    To stop - type Control-C.
    -v              Verbose output.

Advanced options:
    -wa timeout     Timeout in milliseconds to wait for all probes.
    -a              Resolve addresses to hostnames.
    -np count       Number of pings per probe to send (default: 1).
    -i TTL          Time To Live.
    -l size         Send buffer size.
    -f              Set Don't Fragment flag in packet (IPv4-only).
    -4              Force using IPv4.
    -6              Force using IPv6.
    --api-key key   Set web API key.
    --api-url url   Set web API URL.
    --no-delays     Disable delays during printing of results to console.
    --debug         Additional debug output.

Return Codes:
    0 - eRetCode::OK
   10 - eRetCode::BadArguments
   20 - eRetCode::NotSupported
   50 - eRetCode::Cancelled
  100 - eRetCode::ApiFailure
  110 - eRetCode::ApiParsingFail
  500 - eRetCode::OtherError
 1000 - eRetCode::HardFailure

Examples:
dping --list-country
dping --list-asn ES
dping --country US 8.8.8.8
dping --asn AS3352 8.8.8.8

```

### Example

#### --list-country
```
$ dping --list-country
ID Country Name                             Number of probes
-----------------------------------------------------------
RU Russian Federation                       18064
FR France                                    5337
DE Germany                                   5157
CZ Czech Republic                            2247
IT Italy                                     2232
HU Hungary                                   2134
ES Spain                                     2065
TR Turkey                                    1627
...
A2 Satellite Provider                           1
SC Seychelles                                   1
```

#### --list-asn
```
$ dping --list-asn ES
ASN id   Probes ASN name
--------------------------------------------------------
AS3352      836 TELEFONICA DE ESPANA
AS6739      282 Cableuropa - ONO
AS12479     275 France Telecom Espana SA
AS12715     257 Jazz Telecom S.A.
AS12357     143 VODAFONE ESPANA S.A.U.
AS12338      35 Euskaltel S.A.
AS12334      34 R Cable y Telecomunicaciones Galicia, S.A.
AS12430      32 VODAFONE ESPANA S.A.U.
...
AS199343      1 TV Loja Comunicaciones, S.L.
AS199435      1 Wimax On Line, S.L.
```

#### --country
```
$ dping --country US -a 8.8.8.8

Pinging 8.8.8.8 with 32 bytes of data from country code US:
Request timed out.
Reply from google-public-dns-a.google.com [8.8.8.8]: bytes=32 time=18ms TTL=55
Reply from google-public-dns-a.google.com [8.8.8.8]: bytes=32 time=10ms TTL=55
Reply from google-public-dns-a.google.com [8.8.8.8]: bytes=32 time=23ms TTL=55
Reply from google-public-dns-a.google.com [8.8.8.8]: bytes=32 time=24ms TTL=55
Reply from google-public-dns-a.google.com [8.8.8.8]: bytes=32 time=181ms TTL=55

Ping statistics for 8.8.8.8
    Packets : Sent = 6, Received = 5, Lost = 1 (16% loss),
Approximate round trip times in milli-seconds:
    Minimum = 10ms, Maximum = 181ms, Average = 51ms
```

#### --asn
```
$ dping --asn AS3352 -a 8.8.8.8

Pinging 8.8.8.8 with 32 bytes of data from AS3352:
Reply from google-public-dns-a.google.com [8.8.8.8]: bytes=32 time=53ms TTL=55
Reply from google-public-dns-a.google.com [8.8.8.8]: bytes=32 time=61ms TTL=55
Reply from google-public-dns-a.google.com [8.8.8.8]: bytes=32 time=59ms TTL=55
Reply from google-public-dns-a.google.com [8.8.8.8]: bytes=32 time=92ms TTL=55

Ping statistics for 8.8.8.8
    Packets : Sent = 4, Received = 4, Lost = 0 (0% loss),
Approximate round trip times in milli-seconds:
    Minimum = 53ms, Maximum = 92ms, Average = 66ms
```
