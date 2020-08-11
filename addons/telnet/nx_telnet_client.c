/**************************************************************************/
/*                                                                        */
/*       Copyright (c) Microsoft Corporation. All rights reserved.        */
/*                                                                        */
/*       This software is licensed under the Microsoft Software License   */
/*       Terms for Microsoft Azure RTOS. Full text of the license can be  */
/*       found in the LICENSE file at https://aka.ms/AzureRTOS_EULA       */
/*       and in the root directory of this software.                      */
/*                                                                        */
/**************************************************************************/


/**************************************************************************/
/**************************************************************************/
/**                                                                       */
/** NetX Component                                                        */
/**                                                                       */
/**   TELNET Client Protocol                                              */ 
/**                                                                       */
/**************************************************************************/
/**************************************************************************/

#define NX_TELNET_SOURCE_CODE


/* Force error checking to be disabled in this module */

#ifndef NX_DISABLE_ERROR_CHECKING
#define NX_DISABLE_ERROR_CHECKING
#endif

/* Include necessary system files.  */

#include    "nx_api.h"
#include    "nx_ip.h"
#include    "nx_telnet_client.h"



/* Bring in externs for caller checking code.  */

NX_CALLER_CHECKING_EXTERNS


/**************************************************************************/ 
/*                                                                        */ 
/*  FUNCTION                                               RELEASE        */ 
/*                                                                        */ 
/*    _nx_telnet_client_connect                           PORTABLE C      */ 
/*                                                           6.0          */
/*  AUTHOR                                                                */
/*                                                                        */
/*    Yuxin Zhou, Microsoft Corporation                                   */
/*                                                                        */
/*  DESCRIPTION                                                           */ 
/*                                                                        */ 
/*    This function connects a previously created TELNET instance with    */ 
/*    the TCP port at the specified address.                              */ 
/*                                                                        */ 
/*                                                                        */ 
/*  INPUT                                                                 */ 
/*                                                                        */ 
/*    client_ptr                            Pointer to TELNET client      */ 
/*    server_ip_address                     TELNET server address         */ 
/*    server_port                           Server TCP port (usually 23)  */ 
/*    wait_option                           Specifies how long to wait    */ 
/*                                                                        */ 
/*  OUTPUT                                                                */ 
/*                                                                        */ 
/*    status                                Completion status             */ 
/*                                                                        */ 
/*  CALLS                                                                 */ 
/*                                                                        */ 
/*    nx_tcp_client_socket_connect          Connect to TELNET server      */ 
/*    nx_tcp_client_socket_bind             Bind client socket to port    */ 
/*    nx_tcp_client_socket_unbind           Unbind client socket from port*/ 
/*                                                                        */ 
/*  CALLED BY                                                             */ 
/*                                                                        */ 
/*    Application Code                                                    */ 
/*                                                                        */ 
/*  RELEASE HISTORY                                                       */ 
/*                                                                        */ 
/*    DATE              NAME                      DESCRIPTION             */
/*                                                                        */
/*  05-19-2020     Yuxin Zhou               Initial Version 6.0           */
/*                                                                        */
/**************************************************************************/
UINT  _nx_telnet_client_connect(NX_TELNET_CLIENT *client_ptr, ULONG server_ip_address, 
                                UINT server_port, ULONG wait_option)

{

UINT        status;


    /* Determine if the client is still in a not connected state.  */
    if (client_ptr -> nx_telnet_client_socket.nx_tcp_socket_state != NX_TCP_CLOSED)
    {

        /* Already connected, return an error.  */
        return(NX_TELNET_NOT_DISCONNECTED);
    }

    /* Bind the client control socket.  */
    status =  nx_tcp_client_socket_bind(&(client_ptr -> nx_telnet_client_socket), NX_ANY_PORT, wait_option);

    /* Check for an error.  */
    if (status != NX_SUCCESS)
    {

        /* Unable to bind socket to port. */
        return(status);
    }

    /* Connect the socket to the TELNET server.  */
    status =  nx_tcp_client_socket_connect(&(client_ptr -> nx_telnet_client_socket),
                                           server_ip_address, server_port, wait_option); 

    /* Check for an error.  */
    if (status != NX_SUCCESS)
    {

        /* Unbind the socket.  */
        nx_tcp_client_socket_unbind(&(client_ptr -> nx_telnet_client_socket));

        /* Unable to connect socket to server TELNET control port. */
        return(status);
    }

    /* Return success to caller.  */
    return(NX_SUCCESS);
}



/**************************************************************************/ 
/*                                                                        */ 
/*  FUNCTION                                               RELEASE        */ 
/*                                                                        */ 
/*    _nxe_telnet_client_connect                          PORTABLE C      */ 
/*                                                           6.0          */
/*  AUTHOR                                                                */
/*                                                                        */
/*    Yuxin Zhou, Microsoft Corporation                                   */
/*                                                                        */
/*  DESCRIPTION                                                           */ 
/*                                                                        */ 
/*    This function checks for errors in the TELNET client connect call.  */ 
/*                                                                        */ 
/*                                                                        */ 
/*  INPUT                                                                 */ 
/*                                                                        */ 
/*    client_ptr                            Pointer to TELNET client      */ 
/*    server_ip                             TELNET server IP address      */ 
/*    server_port                           Server TCP port (usually 23)  */ 
/*    wait_option                           Specifies how long to wait    */ 
/*                                                                        */ 
/*  OUTPUT                                                                */ 
/*                                                                        */ 
/*    status                                Completion status             */ 
/*                                                                        */ 
/*  CALLS                                                                 */ 
/*                                                                        */ 
/*    _nxe_telnet_client_connect            Actual client connect call    */ 
/*                                                                        */ 
/*  CALLED BY                                                             */ 
/*                                                                        */ 
/*    Application Code                                                    */ 
/*                                                                        */ 
/*  RELEASE HISTORY                                                       */ 
/*                                                                        */ 
/*    DATE              NAME                      DESCRIPTION             */
/*                                                                        */
/*  05-19-2020     Yuxin Zhou               Initial Version 6.0           */
/*                                                                        */
/**************************************************************************/
UINT  _nxe_telnet_client_connect(NX_TELNET_CLIENT *client_ptr, ULONG server_ip, UINT server_port, ULONG wait_option)
{

UINT    status;


    /* Check for invalid input pointers.  */
    if ((client_ptr == NX_NULL) || (client_ptr -> nx_telnet_client_id != NX_TELNET_CLIENT_ID))
        return(NX_PTR_ERROR);

    /* Check for an invalid server IP address.  */
    if (server_ip == 0)
        return(NX_IP_ADDRESS_ERROR);

    /* Check for appropriate caller.  */
    NX_THREADS_ONLY_CALLER_CHECKING

    /* Call actual client connect function.  */
    status =  _nx_telnet_client_connect(client_ptr, server_ip, server_port, wait_option);

    /* Return completion status.  */
    return(status);
}




/**************************************************************************/ 
/*                                                                        */ 
/*  FUNCTION                                               RELEASE        */ 
/*                                                                        */ 
/*    _nxe_telnet_client_create                           PORTABLE C      */ 
/*                                                           6.0          */
/*  AUTHOR                                                                */
/*                                                                        */
/*    Yuxin Zhou, Microsoft Corporation                                   */
/*                                                                        */
/*  DESCRIPTION                                                           */ 
/*                                                                        */ 
/*    This function checks for errors in the TELNET client create call.   */ 
/*                                                                        */ 
/*                                                                        */ 
/*  INPUT                                                                 */ 
/*                                                                        */ 
/*    client_ptr                            Pointer to TELNET client      */ 
/*    client_name                           Name of this TELNET client    */ 
/*    ip_ptr                                Pointer to IP instance        */ 
/*    window_size                           Size of TCP receive window    */ 
/*                                                                        */ 
/*  OUTPUT                                                                */ 
/*                                                                        */ 
/*    status                                Completion status             */ 
/*                                                                        */ 
/*  CALLS                                                                 */ 
/*                                                                        */ 
/*    _nx_telnet_client_create              Actual client create call     */ 
/*                                                                        */ 
/*  CALLED BY                                                             */ 
/*                                                                        */ 
/*    Application Code                                                    */ 
/*                                                                        */ 
/*  RELEASE HISTORY                                                       */ 
/*                                                                        */ 
/*    DATE              NAME                      DESCRIPTION             */
/*                                                                        */
/*  05-19-2020     Yuxin Zhou               Initial Version 6.0           */
/*                                                                        */
/**************************************************************************/
UINT  _nxe_telnet_client_create(NX_TELNET_CLIENT *client_ptr, CHAR *client_name, NX_IP *ip_ptr, ULONG window_size)
{

UINT    status;


    /* Check for invalid input pointers.  */
    if ((ip_ptr == NX_NULL) || (ip_ptr -> nx_ip_id != NX_IP_ID) || 
        (client_ptr == NX_NULL) || (client_ptr -> nx_telnet_client_id == NX_TELNET_CLIENT_ID))
        return(NX_PTR_ERROR);

    /* Call actual client create function.  */
    status =  _nx_telnet_client_create(client_ptr, client_name, ip_ptr, window_size);

    /* Return completion status.  */
    return(status);
}


/**************************************************************************/ 
/*                                                                        */ 
/*  FUNCTION                                               RELEASE        */ 
/*                                                                        */ 
/*    _nx_telnet_client_create                            PORTABLE C      */ 
/*                                                           6.0          */
/*  AUTHOR                                                                */
/*                                                                        */
/*    Yuxin Zhou, Microsoft Corporation                                   */
/*                                                                        */
/*  DESCRIPTION                                                           */ 
/*                                                                        */ 
/*    This function creates an TELNET client instance.                    */ 
/*                                                                        */ 
/*                                                                        */ 
/*  INPUT                                                                 */ 
/*                                                                        */ 
/*    client_ptr                            Pointer to TELNET client      */ 
/*    client_name                           Name of this TELNET client    */ 
/*    ip_ptr                                Pointer to IP instance        */ 
/*    window_size                           Size of TCP receive window    */ 
/*                                                                        */ 
/*  OUTPUT                                                                */ 
/*                                                                        */ 
/*    status                                Completion status             */ 
/*                                                                        */ 
/*  CALLS                                                                 */ 
/*                                                                        */ 
/*    nx_tcp_socket_create                  Create TCP socket             */ 
/*                                                                        */ 
/*  CALLED BY                                                             */ 
/*                                                                        */ 
/*    Application Code                                                    */ 
/*                                                                        */ 
/*  RELEASE HISTORY                                                       */ 
/*                                                                        */ 
/*    DATE              NAME                      DESCRIPTION             */
/*                                                                        */
/*  05-19-2020     Yuxin Zhou               Initial Version 6.0           */
/*                                                                        */
/**************************************************************************/
UINT  _nx_telnet_client_create(NX_TELNET_CLIENT *client_ptr, CHAR *client_name, NX_IP *ip_ptr, ULONG window_size)
{

UINT    status;


    /* Clear the client TELNET control block.  */
    memset((void *) client_ptr, 0, sizeof(NX_TELNET_CLIENT));

    /* Create the TCP control socket.  */
    status =  nx_tcp_socket_create(ip_ptr, &(client_ptr -> nx_telnet_client_socket), client_name, 
                                        NX_TELNET_TOS, NX_TELNET_FRAGMENT_OPTION, NX_TELNET_TIME_TO_LIVE, window_size,
                                        NX_NULL, NX_NULL);

    /* Check for an error.  */
    if (status)
    {

        /* Return an error.  */
        return(NX_TELNET_ERROR);
    }
                                         
    /* Save off the remaining information.  */

    /* Save the client name.  */
    client_ptr -> nx_telnet_client_name =  client_name;

    /* Save the IP pointer.  */
    client_ptr -> nx_telnet_client_ip_ptr =  ip_ptr;

    /* Set the TELNET client id.  */
    client_ptr -> nx_telnet_client_id =  NX_TELNET_CLIENT_ID;

    /* Return success to caller.  */
    return(NX_SUCCESS);
}



/**************************************************************************/ 
/*                                                                        */ 
/*  FUNCTION                                               RELEASE        */ 
/*                                                                        */ 
/*    _nxe_telnet_client_delete                           PORTABLE C      */ 
/*                                                           6.0          */
/*  AUTHOR                                                                */
/*                                                                        */
/*    Yuxin Zhou, Microsoft Corporation                                   */
/*                                                                        */
/*  DESCRIPTION                                                           */ 
/*                                                                        */ 
/*    This function checks for errors in the TELNET client delete call.   */ 
/*                                                                        */ 
/*                                                                        */ 
/*  INPUT                                                                 */ 
/*                                                                        */ 
/*    client_ptr                            Pointer to TELNET client      */ 
/*                                                                        */ 
/*  OUTPUT                                                                */ 
/*                                                                        */ 
/*    status                                Completion status             */ 
/*                                                                        */ 
/*  CALLS                                                                 */ 
/*                                                                        */ 
/*    _nx_telnet_client_delete              Actual client delete call     */ 
/*                                                                        */ 
/*  CALLED BY                                                             */ 
/*                                                                        */ 
/*    Application Code                                                    */ 
/*                                                                        */ 
/*  RELEASE HISTORY                                                       */ 
/*                                                                        */ 
/*    DATE              NAME                      DESCRIPTION             */
/*                                                                        */
/*  05-19-2020     Yuxin Zhou               Initial Version 6.0           */
/*                                                                        */
/**************************************************************************/
UINT  _nxe_telnet_client_delete(NX_TELNET_CLIENT *client_ptr)
{

UINT    status;


    /* Check for invalid input pointers.  */
    if ((client_ptr == NX_NULL) || (client_ptr -> nx_telnet_client_id != NX_TELNET_CLIENT_ID))
        return(NX_PTR_ERROR);

    /* Check for appropriate caller.  */
    NX_THREADS_ONLY_CALLER_CHECKING

    /* Call actual client delete function.  */
    status =  _nx_telnet_client_delete(client_ptr);

    /* Return completion status.  */
    return(status);
}


/**************************************************************************/ 
/*                                                                        */ 
/*  FUNCTION                                               RELEASE        */ 
/*                                                                        */ 
/*    _nx_telnet_client_delete                            PORTABLE C      */ 
/*                                                           6.0          */
/*  AUTHOR                                                                */
/*                                                                        */
/*    Yuxin Zhou, Microsoft Corporation                                   */
/*                                                                        */
/*  DESCRIPTION                                                           */ 
/*                                                                        */ 
/*    This function deletes a previously created TELNET client instance.  */ 
/*                                                                        */ 
/*                                                                        */ 
/*  INPUT                                                                 */ 
/*                                                                        */ 
/*    client_ptr                            Pointer to TELNET client      */ 
/*                                                                        */ 
/*  OUTPUT                                                                */ 
/*                                                                        */ 
/*    status                                Completion status             */ 
/*                                                                        */ 
/*  CALLS                                                                 */ 
/*                                                                        */ 
/*    nx_tcp_socket_delete                  Delete TCP socket             */ 
/*                                                                        */ 
/*  CALLED BY                                                             */ 
/*                                                                        */ 
/*    Application Code                                                    */ 
/*                                                                        */ 
/*  RELEASE HISTORY                                                       */ 
/*                                                                        */ 
/*    DATE              NAME                      DESCRIPTION             */
/*                                                                        */
/*  05-19-2020     Yuxin Zhou               Initial Version 6.0           */
/*                                                                        */
/**************************************************************************/
UINT  _nx_telnet_client_delete(NX_TELNET_CLIENT *client_ptr)
{

    /* Determine if the client is still in an established state.  */
    if (client_ptr -> nx_telnet_client_socket.nx_tcp_socket_state == NX_TCP_ESTABLISHED)
    {

        /* Still connected, return an error.  */
        return(NX_TELNET_NOT_DISCONNECTED);
    }

    /* Delete the socket.  */
    nx_tcp_socket_delete(&(client_ptr -> nx_telnet_client_socket));

    /* Return success to caller.  */
    return(NX_SUCCESS);
}


/**************************************************************************/ 
/*                                                                        */ 
/*  FUNCTION                                               RELEASE        */ 
/*                                                                        */ 
/*    _nxe_telnet_client_disconnect                       PORTABLE C      */ 
/*                                                           6.0          */
/*  AUTHOR                                                                */
/*                                                                        */
/*    Yuxin Zhou, Microsoft Corporation                                   */
/*                                                                        */
/*  DESCRIPTION                                                           */ 
/*                                                                        */ 
/*    This function checks for errors in the TELNET client disconnect.    */ 
/*                                                                        */ 
/*                                                                        */ 
/*  INPUT                                                                 */ 
/*                                                                        */ 
/*    client_ptr                            Pointer to TELNET client      */ 
/*    wait_option                           Specifies how long to wait    */ 
/*                                                                        */ 
/*  OUTPUT                                                                */ 
/*                                                                        */ 
/*    status                                Completion status             */ 
/*                                                                        */ 
/*  CALLS                                                                 */ 
/*                                                                        */ 
/*    _nx_telnet_client_disconnect          Actual client disconnect call */ 
/*                                                                        */ 
/*  CALLED BY                                                             */ 
/*                                                                        */ 
/*    Application Code                                                    */ 
/*                                                                        */ 
/*  RELEASE HISTORY                                                       */ 
/*                                                                        */ 
/*    DATE              NAME                      DESCRIPTION             */
/*                                                                        */
/*  05-19-2020     Yuxin Zhou               Initial Version 6.0           */
/*                                                                        */
/**************************************************************************/
UINT  _nxe_telnet_client_disconnect(NX_TELNET_CLIENT *client_ptr, ULONG wait_option)
{

UINT    status;


    /* Check for invalid input pointers.  */
    if ((client_ptr == NX_NULL) || (client_ptr -> nx_telnet_client_id != NX_TELNET_CLIENT_ID))
        return(NX_PTR_ERROR);

    /* Check for appropriate caller.  */
    NX_THREADS_ONLY_CALLER_CHECKING

    /* Call actual client disconnect function.  */
    status =  _nx_telnet_client_disconnect(client_ptr, wait_option);

    /* Return completion status.  */
    return(status);
}


/**************************************************************************/ 
/*                                                                        */ 
/*  FUNCTION                                               RELEASE        */ 
/*                                                                        */ 
/*    _nx_telnet_client_disconnect                        PORTABLE C      */ 
/*                                                           6.0          */
/*  AUTHOR                                                                */
/*                                                                        */
/*    Yuxin Zhou, Microsoft Corporation                                   */
/*                                                                        */
/*  DESCRIPTION                                                           */ 
/*                                                                        */ 
/*    This function disconnects a previously established TELNET           */ 
/*    connection.                                                         */ 
/*                                                                        */ 
/*                                                                        */ 
/*  INPUT                                                                 */ 
/*                                                                        */ 
/*    client_ptr                            Pointer to TELNET client      */ 
/*    wait_option                           Specifies how long to wait    */ 
/*                                                                        */ 
/*  OUTPUT                                                                */ 
/*                                                                        */ 
/*    status                                Completion status             */ 
/*                                                                        */ 
/*  CALLS                                                                 */ 
/*                                                                        */ 
/*    nx_tcp_client_socket_unbind           Unbind a socket               */ 
/*    nx_tcp_socket_disconnect              Disconnect a socket           */ 
/*                                                                        */ 
/*  CALLED BY                                                             */ 
/*                                                                        */ 
/*    Application Code                                                    */ 
/*                                                                        */ 
/*  RELEASE HISTORY                                                       */ 
/*                                                                        */ 
/*    DATE              NAME                      DESCRIPTION             */
/*                                                                        */
/*  05-19-2020     Yuxin Zhou               Initial Version 6.0           */
/*                                                                        */
/**************************************************************************/
UINT  _nx_telnet_client_disconnect(NX_TELNET_CLIENT *client_ptr, ULONG wait_option)
{


    /* Determine if the client is still in an established state.  */
    if (client_ptr -> nx_telnet_client_socket.nx_tcp_socket_state != NX_TCP_ESTABLISHED)
    {

        /* Not connected, return an error.  */
        return(NX_TELNET_NOT_CONNECTED);
    }

    /* Disconnect and unbind the socket.  */
    nx_tcp_socket_disconnect(&(client_ptr -> nx_telnet_client_socket), wait_option);
    nx_tcp_client_socket_unbind(&(client_ptr -> nx_telnet_client_socket));

    /* Return success to caller.  */
    return(NX_SUCCESS);
}


/**************************************************************************/ 
/*                                                                        */ 
/*  FUNCTION                                               RELEASE        */ 
/*                                                                        */ 
/*    _nxe_telnet_client_packet_receive                   PORTABLE C      */ 
/*                                                           6.0          */
/*  AUTHOR                                                                */
/*                                                                        */
/*    Yuxin Zhou, Microsoft Corporation                                   */
/*                                                                        */
/*  DESCRIPTION                                                           */ 
/*                                                                        */ 
/*    This function checks for errors in the TELNET client packet         */ 
/*    receive call.                                                       */ 
/*                                                                        */ 
/*                                                                        */ 
/*  INPUT                                                                 */ 
/*                                                                        */ 
/*    client_ptr                            Pointer to TELNET client      */ 
/*    packet_ptr                            Destination for packet ptr    */ 
/*    wait_option                           Specifies how long to wait    */ 
/*                                                                        */ 
/*  OUTPUT                                                                */ 
/*                                                                        */ 
/*    status                                Completion status             */ 
/*                                                                        */ 
/*  CALLS                                                                 */ 
/*                                                                        */ 
/*    _nx_telnet_client_packet_receive      Actual client packet receive  */ 
/*                                            call                        */ 
/*                                                                        */ 
/*  CALLED BY                                                             */ 
/*                                                                        */ 
/*    Application Code                                                    */ 
/*                                                                        */ 
/*  RELEASE HISTORY                                                       */ 
/*                                                                        */ 
/*    DATE              NAME                      DESCRIPTION             */
/*                                                                        */
/*  05-19-2020     Yuxin Zhou               Initial Version 6.0           */
/*                                                                        */
/**************************************************************************/
UINT  _nxe_telnet_client_packet_receive(NX_TELNET_CLIENT *client_ptr, NX_PACKET **packet_ptr, ULONG wait_option)
{

UINT    status;


    /* Check for invalid input pointers.  */
    if ((client_ptr == NX_NULL) || (client_ptr -> nx_telnet_client_id != NX_TELNET_CLIENT_ID) || (packet_ptr == NX_NULL))
        return(NX_PTR_ERROR);

    /* Check for appropriate caller.  */
    NX_THREADS_ONLY_CALLER_CHECKING

    /* Call actual client packet receive function.  */
    status =  _nx_telnet_client_packet_receive(client_ptr, packet_ptr, wait_option);

    /* Return completion status.  */
    return(status);
}


/**************************************************************************/ 
/*                                                                        */ 
/*  FUNCTION                                               RELEASE        */ 
/*                                                                        */ 
/*    _nx_telnet_client_packet_receive                    PORTABLE C      */ 
/*                                                           6.0          */
/*  AUTHOR                                                                */
/*                                                                        */
/*    Yuxin Zhou, Microsoft Corporation                                   */
/*                                                                        */
/*  DESCRIPTION                                                           */ 
/*                                                                        */ 
/*    This function checks for errors in the TELNET client packet         */ 
/*    receive call.                                                       */ 
/*                                                                        */ 
/*                                                                        */ 
/*  INPUT                                                                 */ 
/*                                                                        */ 
/*    client_ptr                            Pointer to TELNET client      */ 
/*    packet_ptr                            Destination for packet ptr    */ 
/*    wait_option                           Specifies how long to wait    */ 
/*                                                                        */ 
/*  OUTPUT                                                                */ 
/*                                                                        */ 
/*    status                                Completion status             */ 
/*                                                                        */ 
/*  CALLS                                                                 */ 
/*                                                                        */ 
/*    nx_tcp_socket_receive                 Receive TCP packet            */ 
/*                                                                        */ 
/*  CALLED BY                                                             */ 
/*                                                                        */ 
/*    Application Code                                                    */ 
/*                                                                        */ 
/*  RELEASE HISTORY                                                       */ 
/*                                                                        */ 
/*    DATE              NAME                      DESCRIPTION             */
/*                                                                        */
/*  05-19-2020     Yuxin Zhou               Initial Version 6.0           */
/*                                                                        */
/**************************************************************************/
UINT  _nx_telnet_client_packet_receive(NX_TELNET_CLIENT *client_ptr, NX_PACKET **packet_ptr, ULONG wait_option)
{

UINT    status;

    /* Attempt to receive a packet from the TCP socket.  */
    status =  nx_tcp_socket_receive(&(client_ptr -> nx_telnet_client_socket), packet_ptr, wait_option);

    /* Return completion status.  */
    return(status);
}


/**************************************************************************/ 
/*                                                                        */ 
/*  FUNCTION                                               RELEASE        */ 
/*                                                                        */ 
/*    _nxe_telnet_client_packet_send                      PORTABLE C      */ 
/*                                                           6.0          */
/*  AUTHOR                                                                */
/*                                                                        */
/*    Yuxin Zhou, Microsoft Corporation                                   */
/*                                                                        */
/*  DESCRIPTION                                                           */ 
/*                                                                        */ 
/*    This function checks for errors in the TELNET client packet         */ 
/*    send call.                                                          */ 
/*                                                                        */ 
/*                                                                        */ 
/*  INPUT                                                                 */ 
/*                                                                        */ 
/*    client_ptr                            Pointer to TELNET client      */ 
/*    packet_ptr                            Pointer to packet to send     */ 
/*    wait_option                           Specifies how long to wait    */ 
/*                                                                        */ 
/*  OUTPUT                                                                */ 
/*                                                                        */ 
/*    status                                Completion status             */ 
/*                                                                        */ 
/*  CALLS                                                                 */ 
/*                                                                        */ 
/*    _nx_telnet_client_packet_send         Actual client packet send     */ 
/*                                            call                        */ 
/*                                                                        */ 
/*  CALLED BY                                                             */ 
/*                                                                        */ 
/*    Application Code                                                    */ 
/*                                                                        */ 
/*  RELEASE HISTORY                                                       */ 
/*                                                                        */ 
/*    DATE              NAME                      DESCRIPTION             */
/*                                                                        */
/*  05-19-2020     Yuxin Zhou               Initial Version 6.0           */
/*                                                                        */
/**************************************************************************/
UINT  _nxe_telnet_client_packet_send(NX_TELNET_CLIENT *client_ptr, NX_PACKET *packet_ptr, ULONG wait_option)
{

UINT    status;


    /* Check for invalid input pointers.  */
    if ((client_ptr == NX_NULL) || (client_ptr -> nx_telnet_client_id != NX_TELNET_CLIENT_ID) || (packet_ptr == NX_NULL))
        return(NX_PTR_ERROR);

    /* Check for appropriate caller.  */
    NX_THREADS_ONLY_CALLER_CHECKING

    /* Call actual client packet send function.  */
    status =  _nx_telnet_client_packet_send(client_ptr, packet_ptr, wait_option);

    /* Return completion status.  */
    return(status);
}


/**************************************************************************/ 
/*                                                                        */ 
/*  FUNCTION                                               RELEASE        */ 
/*                                                                        */ 
/*    _nx_telnet_client_packet_send                       PORTABLE C      */ 
/*                                                           6.0          */
/*  AUTHOR                                                                */
/*                                                                        */
/*    Yuxin Zhou, Microsoft Corporation                                   */
/*                                                                        */
/*  DESCRIPTION                                                           */ 
/*                                                                        */ 
/*    This function checks for errors in the TELNET client packet         */ 
/*    send call.                                                          */ 
/*                                                                        */ 
/*                                                                        */ 
/*  INPUT                                                                 */ 
/*                                                                        */ 
/*    client_ptr                            Pointer to TELNET client      */ 
/*    packet_ptr                            Pointer to packet to send     */ 
/*    wait_option                           Specifies how long to wait    */ 
/*                                                                        */ 
/*  OUTPUT                                                                */ 
/*                                                                        */ 
/*    status                                Completion status             */ 
/*                                                                        */ 
/*  CALLS                                                                 */ 
/*                                                                        */ 
/*    nx_tcp_socket_send                    Send TCP packet               */ 
/*                                                                        */ 
/*  CALLED BY                                                             */ 
/*                                                                        */ 
/*    Application Code                                                    */ 
/*                                                                        */ 
/*  RELEASE HISTORY                                                       */ 
/*                                                                        */ 
/*    DATE              NAME                      DESCRIPTION             */
/*                                                                        */
/*  05-19-2020     Yuxin Zhou               Initial Version 6.0           */
/*                                                                        */
/**************************************************************************/
UINT  _nx_telnet_client_packet_send(NX_TELNET_CLIENT *client_ptr, NX_PACKET *packet_ptr, ULONG wait_option)
{

UINT    status;

    /* Attempt to send a packet on the TCP socket.  */
    status =  nx_tcp_socket_send(&(client_ptr -> nx_telnet_client_socket), packet_ptr, wait_option);

    /* Return completion status.  */
    return(status);
}
