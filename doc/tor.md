# TOR SUPPORT IN remita

It is possible to run remita as a Tor hidden service, and connect to such services.

The following directions assume you have a Tor proxy running on port 9050. Many distributions default to having a SOCKS proxy listening on port 9050, but others may not. In particular, the Tor Browser Bundle defaults to listening on port 9150. See [Tor Project FAQ:TBBSocksPort](https://www.torproject.org/docs/faq.html.en#TBBSocksPort) for how to properly
configure Tor.


## 1. Run remita behind a Tor proxy
----------------------------------

The first step is running remita behind a Tor proxy. This will already anonymize all
outgoing connections, but more is possible.

	-proxy=ip:port  Set the proxy server. If SOCKS5 is selected (default), this proxy
	                server will be used to try to reach .onion addresses as well.

	-onion=ip:port  Set the proxy server to use for Tor hidden services. You do not
	                need to set this if it's the same as -proxy. You can use -noonion
	                to explicitly disable access to hidden services.

	-listen         When using -proxy, listening is disabled by default. If you want
	                to run a hidden service (see next section), you'll need to enable
	                it explicitly.

	-connect=X      When behind a Tor proxy, you can specify .onion addresses instead
	-addnode=X      of IP addresses or hostnames in these parameters. It requires
	-seednode=X     SOCKS5. In Tor mode, such addresses can also be exchanged with
	                other P2P nodes.

	-onlynet=onion  Make outgoing connections only to .onion addresses. Incoming
	                connections are not affected by this option. This option can be
	                specified multiple times to allow multiple network types, e.g.
	                ipv4, ipv6, or onion.

In a typical situation, this suffices to run behind a Tor proxy:

	./remitad -proxy=127.0.0.1:9050


## 2. Run a remita hidden server

If you configure your Tor system accordingly, it is possible to make your node also
reachable from the Tor network. Add these lines to your /etc/tor/torrc (or equivalent
config file): *Needed for Tor version 0.2.7.0 and older versions of Tor only. For newer
versions of Tor see [Section 3](#3-automatically-listen-on-tor).*

	HiddenServiceDir /var/lib/tor/remita-service/
	HiddenServiceVersion 2
	HiddenServicePort 8351 127.0.0.1:8351
	HiddenServicePort 61472 127.0.0.1:61472

The directory can be different of course, but (both) port numbers should be equal to
your remitad's P2P listen port (8351 by default).

	-externalip=X   You can tell remita about its publicly reachable address using
	                this option, and this can be a v2 .onion address (v3 .onion
	                addresses are not supported by the remita network). Given the above
	                configuration, you can find your .onion address in
	                /var/lib/tor/remita-service/hostname. For connections
	                coming from unroutable addresses (such as 127.0.0.1, where the
	                Tor proxy typically runs), .onion addresses are given
	                preference for your node to advertise itself with.

	-listen         You'll need to enable listening for incoming connections, as this
	                is off by default behind a proxy.

	-discover       When -externalip is specified, no attempt is made to discover local
	                IPv4 or IPv6 addresses. If you want to run a dual stack, reachable
	                from both Tor and IPv4 (or IPv6), you'll need to either pass your
	                other addresses using -externalip, or explicitly enable -discover.
	                Note that both addresses of a dual-stack system may be easily
	                linkable using traffic analysis.

In a typical situation, where you're only reachable via Tor, this should suffice:

	./remitad -proxy=127.0.0.1:9050 -externalip=remitazj6l4cvo2fxy.onion -listen

(obviously, replace the .onion address with your own). It should be noted that you still
listen on all devices and another node could establish a clearnet connection, when knowing
your address. To mitigate this, additionally bind the address of your Tor proxy:

	./remitad ... -bind=127.0.0.1

If you don't care too much about hiding your node, and want to be reachable on IPv4
as well, use `discover` instead:

	./remitad ... -discover

and open port 8351 on your firewall (or use -upnp).

If you only want to use Tor to reach .onion addresses, but not use it as a proxy
for normal IPv4/IPv6 communication, use:

	./remitad -onion=127.0.0.1:9050 -externalip=remitazj6l4cvo2fxy.onion -discover

## 3. Automatically listen on Tor

Starting with Tor version 0.2.7.1 it is possible, through Tor's control socket
API, to create and destroy 'ephemeral' hidden services programmatically.
remita has been updated to make use of this.

This means that if Tor is running (and proper authentication has been configured),
remita automatically creates a hidden service to listen on. This will positively
affect the number of available .onion nodes.

This new feature is enabled by default if remita is listening (`-listen`), and
requires a Tor connection to work. It can be explicitly disabled with `-listenonion=0`
and, if not disabled, configured using the `-torcontrol` and `-torpassword` settings.
To show verbose debugging information, pass `-debug=tor`.

Connecting to Tor's control socket API requires one of two authentication methods to be
configured. It also requires the control socket to be enabled, e.g. put `ControlPort 9051`
in `torrc` config file. For cookie authentication the user running remitad must have read
access to the `CookieAuthFile` specified in Tor configuration. In some cases this is
preconfigured and the creation of a hidden service is automatic. If permission problems
are seen with `-debug=tor` they can be resolved by adding both the user running Tor and
the user running remitad to the same group and setting permissions appropriately. On
Debian-based systems the user running remitad can be added to the debian-tor group,
which has the appropriate permissions.

An alternative authentication method is the use
of the `-torpassword=password` option. The `password` is the clear text form that
was used when generating the hashed password for the `HashedControlPassword` option
in the tor configuration file. The hashed password can be obtained with the command
`tor --hash-password password` (read the tor manual for more details).

## 4. Privacy recommendations

- Do not add anything but remita ports to the hidden service created in section 2.
  If you run a web service too, create a new hidden service for that.
  Otherwise it is trivial to link them, which may reduce privacy. Hidden
  services created automatically (as in section 3) always have only one port
  open.