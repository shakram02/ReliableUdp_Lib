//
// Created by ahmed on 1/14/17.
//

#ifndef UDPSOCKETLIB_PROTOCOLMSGID_H
#define UDPSOCKETLIB_PROTOCOLMSGID_H

/* Server configuration */
//#define SERVER_IP "192.168.1.7"
#define SERVER_IP "127.0.0.1"
#define PORT_NUM 62135

/* Client configuration */

 
/* Protocol messages format: msg_SENDER */

#define HNDSHK_CLNT "hndshk"
#define ID_HNDSHK_CLNT -1    /* Handshake string */

#define GO_REDIRECT_SRV "redirect"
#define ID_GO_REDIRECT -2   /* redirect(portnum) */

#define REDIRECT_SUCC_CLNT "REDIRECT SUCCESSFUL"
#define ID_REDIRECT_SUCC_CLNT -3 /* REDIRECT SUCCESSFUL */

#define REDIRECT_OK_SRV "OK"
#define ID_REDIRECT_OK_SRV -4  /* ok */

#define FILE_NAME_CLNT "FILE-"
#define ID_FILE_NAME_CLNT -5 /* (filename) */

#define FILE_SZ_SRV "FILESIZE-"
#define ID_FILE_SZ_SRV -6    /* FILESIZE-(count) */

#define FILE_END_CONF_CLNT "BYE"
#define ID_FILE_END_CONF_CLNT -7

#endif //UDPSOCKETLIB_PROTOCOLMSGID_H
