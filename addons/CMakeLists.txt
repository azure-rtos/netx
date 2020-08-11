# Each protocol handler is listed below. If you want
# to disable some / all of these, comment out the block(s) in question

set(SOURCES 
    # {{BEGIN_TARGET_SOURCES}}
	${CMAKE_CURRENT_LIST_DIR}/auto_ip/nx_auto_ip.c
	${CMAKE_CURRENT_LIST_DIR}/bsd/nx_bsd.c
	${CMAKE_CURRENT_LIST_DIR}/dhcp/nx_dhcp_server.c
	${CMAKE_CURRENT_LIST_DIR}/dhcp/nx_dhcp.c
	${CMAKE_CURRENT_LIST_DIR}/dns/nx_dns.c
	${CMAKE_CURRENT_LIST_DIR}/ftp/nx_ftp_client.c
	${CMAKE_CURRENT_LIST_DIR}/ftp/nx_ftp_server.c
	${CMAKE_CURRENT_LIST_DIR}/http/nx_http_client.c
	${CMAKE_CURRENT_LIST_DIR}/http/nx_http_server.c
	${CMAKE_CURRENT_LIST_DIR}/pop3/nx_pop3_client.c
	${CMAKE_CURRENT_LIST_DIR}/ppp/nx_ppp.c
	${CMAKE_CURRENT_LIST_DIR}/pppoe/nx_pppoe_client.c
	${CMAKE_CURRENT_LIST_DIR}/pppoe/nx_pppoe_server.c
	${CMAKE_CURRENT_LIST_DIR}/smtp/nx_smtp_client.c
	${CMAKE_CURRENT_LIST_DIR}/snmp/nx_des.c
	${CMAKE_CURRENT_LIST_DIR}/snmp/nx_sha1.c
	${CMAKE_CURRENT_LIST_DIR}/snmp/nx_snmp.c
	${CMAKE_CURRENT_LIST_DIR}/sntp/nx_sntp_client.c
	${CMAKE_CURRENT_LIST_DIR}/telnet/nx_telnet_client.c
	${CMAKE_CURRENT_LIST_DIR}/telnet/nx_telnet_server.c
	${CMAKE_CURRENT_LIST_DIR}/tftp/nx_tftp_client.c
	${CMAKE_CURRENT_LIST_DIR}/tftp/nx_tftp_server.c

    # {{END_TARGET_SOURCES}}
)

target_sources(${PROJECT_NAME} PRIVATE ${SOURCES})

target_include_directories(${PROJECT_NAME} PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}/auto_ip
    ${CMAKE_CURRENT_LIST_DIR}/bsd
    ${CMAKE_CURRENT_LIST_DIR}/dhcp
    ${CMAKE_CURRENT_LIST_DIR}/dns
    ${CMAKE_CURRENT_LIST_DIR}/ftp
    ${CMAKE_CURRENT_LIST_DIR}/http
    ${CMAKE_CURRENT_LIST_DIR}/pop3
    ${CMAKE_CURRENT_LIST_DIR}/ppp
    ${CMAKE_CURRENT_LIST_DIR}/pppoe
    ${CMAKE_CURRENT_LIST_DIR}/smtp
    ${CMAKE_CURRENT_LIST_DIR}/snmp
    ${CMAKE_CURRENT_LIST_DIR}/sntp
    ${CMAKE_CURRENT_LIST_DIR}/telnet
    ${CMAKE_CURRENT_LIST_DIR}/tftp
)
