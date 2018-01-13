/*
 * Copyright (c) 2004-2005 Sergey Lyubka <valenok@gmail.com>
 * All rights reserved
 *
 * "THE BEER-WARE LICENSE" (Revision 42):
 * Sergey Lyubka wrote this file.  As long as you retain this notice you
 * can do whatever you want with this stuff. If we meet some day, and you think
 * this stuff is worth it, you can buy me a beer in return.
 */

#include "defs.h"

#define ALIAS_URI "/web"

static int	exit_flag;	/* Program termination flag	*/

static void
signal_handler(int sig_num)
{
    switch (sig_num)
    {
#ifndef _WIN32

        case SIGCHLD:
            while (waitpid(-1, &sig_num, WNOHANG) > 0) ;

            break;
#endif /* !_WIN32 */

        default:
            exit_flag = sig_num;
            break;
    }
}



/*
 * This callback function is attached to the "/" and "/abc.html" URIs,
 * thus is acting as "index.html" file. It shows a bunch of links
 * to other URIs, and allows to change the value of program's
 * internal variable. The pointer to that variable is passed to the
 * callback function as arg->user_data.
 */
static void
show_index(struct shttpd_arg *arg)
{
    int		*p = arg->user_data;	/* integer passed to us */
    char		value[20];
    const char	*host, *request_method, *query_string, *request_uri;

    request_method = shttpd_get_env(arg, "REQUEST_METHOD");
    request_uri = shttpd_get_env(arg, "REQUEST_URI");
    query_string = shttpd_get_env(arg, "QUERY_STRING");

    /* Change the value of integer variable */
    value[0] = '\0';

    if (!strcmp(request_method, "POST"))
    {
        /* If not all data is POSTed, wait for the rest */
        if (arg->flags & SHTTPD_MORE_POST_DATA)
            return;

        (void) shttpd_get_var("name1", arg->in.buf, arg->in.len,
                              value, sizeof(value));
    }
    else if (query_string != NULL)
    {
        (void) shttpd_get_var("name1", query_string,
                              strlen(query_string), value, sizeof(value));
    }

    if (value[0] != '\0')
    {
        *p = atoi(value);

        /*
         * Suggested by Luke Dunstan. When POST is used,
         * send 303 code to force the browser to re-request the
         * page using GET method. This prevents the possibility of
         * the user accidentally resubmitting the form when using
         * Refresh or Back commands in the browser.
         */
        if (!strcmp(request_method, "POST"))
        {
            shttpd_printf(arg, "HTTP/1.1 303 See Other\r\n"
                          "Location: %s\r\n\r\n", request_uri);
            arg->flags |= SHTTPD_END_OF_OUTPUT;
            return;
        }
    }

    shttpd_printf(arg, "%s",
                  "HTTP/1.1 200 OK\r\nContent-Type: text/html\r\n\r\n"
                  "<html><body><h1>Welcome to embedded example of SHTTPD");
    shttpd_printf(arg, " v. %s </h1><ul>", shttpd_version());

    shttpd_printf(arg, "<li><code>REQUEST_METHOD: %s "
                  "REQUEST_URI: \"%s\" QUERY_STRING: \"%s\""
                  " REMOTE_ADDR: %s REMOTE_USER: \"(null)\"</code><hr>",
                  request_method, request_uri,
                  query_string ? query_string : "(null)",
                  shttpd_get_env(arg, "REMOTE_ADDR"));
    shttpd_printf(arg, "<li>Internal int variable value: <b>%d</b>", *p);

    shttpd_printf(arg, "%s",
                  "<form method=\"GET\">Enter new value: "
                  "<input type=\"text\" name=\"name1\"/>"
                  "<input type=\"submit\" "
                  "value=\"set new value using GET method\"></form>");
    shttpd_printf(arg, "%s",
                  "<form method=\"POST\">Enter new value: "
                  "<input type=\"text\" name=\"name1\"/>"
                  "<input type=\"submit\" "
                  "value=\"set new value using POST method\"></form>");

    shttpd_printf(arg, "%s",
                  "<hr><li><a href=\"/secret\">"
                  "Protected page</a> (guest:guest)<hr>"
                  "<li><a href=\"/huge\">Output lots of data</a><hr>"
//                  "<li><a href=\"" ALIAS_URI "/\">Aliased " ALIAS_DIR " directory</a><hr>"
                  );
    shttpd_printf(arg, "%s",
                  "<li><a href=\"/Makefile\">Regular file (Makefile)</a><hr>"
                  "<li><a href=\"/ssi_test.shtml\">SSI file "
                  "(ssi_test.shtml)</a><hr>"
                  "<li><a href=\"/users/joe/\">Wildcard URI example</a><hr>"
                  "<li><a href=\"/not-existent/\">Custom 404 handler</a><hr>");

    host = shttpd_get_header(arg, "Host");
    shttpd_printf(arg, "<li>'Host' header value: [%s]<hr>",
                  host ? host : "NOT SET");

    shttpd_printf(arg, "<li>Upload file example. "
                  "<form method=\"post\" enctype=\"multipart/form-data\" "
                  "action=\"/post\"><input type=\"file\" name=\"file\">"
                  "<input type=\"submit\"></form>");

    shttpd_printf(arg, "%s", "</body></html>");
    arg->flags |= SHTTPD_END_OF_OUTPUT;
}


/*
 * This callback function is attached to the "/" and "/abc.html" URIs,
 * thus is acting as "index.html" file. It shows a bunch of links
 * to other URIs, and allows to change the value of program's
 * internal variable. The pointer to that variable is passed to the
 * callback function as arg->user_data.
 */
static void
show_index2(struct shttpd_arg *arg)
{
    int		*p = arg->user_data;	/* integer passed to us */
    char		value[20];
    const char	*host, *request_method, *query_string, *request_uri;

    request_method = shttpd_get_env(arg, "REQUEST_METHOD");
    request_uri = shttpd_get_env(arg, "REQUEST_URI");
    query_string = shttpd_get_env(arg, "QUERY_STRING");

    /* Change the value of integer variable */
    value[0] = '\0';

    if (!strcmp(request_method, "POST"))
    {
        /* If not all data is POSTed, wait for the rest */
        if (arg->flags & SHTTPD_MORE_POST_DATA)
            return;

        (void) shttpd_get_var("name1", arg->in.buf, arg->in.len,
                              value, sizeof(value));
    }
    else if (query_string != NULL)
    {
        (void) shttpd_get_var("name1", query_string,
                              strlen(query_string), value, sizeof(value));
    }

    if (value[0] != '\0')
    {
        *p = atoi(value);

        /*
	         * Suggested by Luke Dunstan. When POST is used,
	         * send 303 code to force the browser to re-request the
	         * page using GET method. This prevents the possibility of
	         * the user accidentally resubmitting the form when using
	         * Refresh or Back commands in the browser.
         */
        if (!strcmp(request_method, "POST"))
        {
            shttpd_printf(arg, "HTTP/1.1 303 See Other\r\n"
                          "Location: %s\r\n\r\n", request_uri);
            arg->flags |= SHTTPD_END_OF_OUTPUT;
            return;
        }
    }

    shttpd_printf(arg, "%s",
                  "HTTP/1.1 200 OK\r\nContent-Type: text/html\r\n\r\n"
                  "<html><body><h1>Welcome to embedded example of SHTTPD");
    shttpd_printf(arg, " v. %s </h1><ul>", shttpd_version());

    shttpd_printf(arg, "<li><code>REQUEST_METHOD: %s "
                  "REQUEST_URI: \"%s\" QUERY_STRING: \"%s\""
                  " REMOTE_ADDR: %s REMOTE_USER: \"(null)\"</code><hr>",
                  request_method, request_uri,
                  query_string ? query_string : "(null)",
                  shttpd_get_env(arg, "REMOTE_ADDR"));
    shttpd_printf(arg, "<li>Internal int variable value: <b>%d</b>", *p);

    shttpd_printf(arg, "%s",
                  "<form method=\"GET\">Enter new value: "
                  "<input type=\"text\" name=\"name1\"/>"
                  "<input type=\"submit\" "
                  "value=\"set new value using GET method\"></form>");
    shttpd_printf(arg, "%s",
                  "<form method=\"POST\">Enter new value: "
                  "<input type=\"text\" name=\"name1\"/>"
                  "<input type=\"submit\" "
                  "value=\"set new value using POST method\"></form>");

    shttpd_printf(arg, "%s",
                  "<hr><li><a href=\"/secret\">"
                  "Protected page</a> (guest:guest)<hr>"
                  "<li><a href=\"/huge\">Output lots of data</a><hr>"
//                  "<li><a href=\"" ALIAS_URI "/\">Aliased " ALIAS_DIR " directory</a><hr>"
                  );
    shttpd_printf(arg, "%s",
                  "<li><a href=\"/Makefile\">Regular file (Makefile)</a><hr>"
                  "<li><a href=\"/ssi_test.shtml\">SSI file "
                  "(ssi_test.shtml)</a><hr>"
                  "<li><a href=\"/users/joe/\">Wildcard URI example</a><hr>"
                  "<li><a href=\"/not-existent/\">Custom 404 handler</a><hr>");

    host = shttpd_get_header(arg, "Host");
    shttpd_printf(arg, "<li>'Host' header value: [%s]<hr>",
                  host ? host : "NOT SET");

    shttpd_printf(arg, "<li>Upload file example. "
                  "<form method=\"post\" enctype=\"multipart/form-data\" "
                  "action=\"/post\"><input type=\"file\" name=\"file\">"
                  "<input type=\"submit\"></form>");

    shttpd_printf(arg, "%s", "</body></html>");
    arg->flags |= SHTTPD_END_OF_OUTPUT;
}

int
main(int argc, char *argv[])
{
    struct shttpd_ctx	*ctx;
	int    data          = 1234567;
	char   strBuf[256]   = {0};
#if !defined(NO_AUTH)

    if (argc > 1 && argv[1][0] == '-' && argv[1][1] == 'A')
    {
        if (argc != 6)
            _shttpd_usage(argv[0]);

        exit(_shttpd_edit_passwords(argv[2], argv[3], argv[4], argv[5]));
    }

#endif /* NO_AUTH */

    if (argc == 2 && (!strcmp(argv[1], "-h") || !strcmp(argv[1], "--help")))
        _shttpd_usage(argv[0]);

#if defined(_WIN32)
    try_to_run_as_nt_service();
#endif /* _WIN32 */

#ifndef _WIN32
    (void) signal(SIGCHLD, signal_handler);
    (void) signal(SIGPIPE, SIG_IGN);
#endif /* _WIN32 */

    (void) signal(SIGTERM, signal_handler);
    (void) signal(SIGINT, signal_handler);


    if ((ctx = shttpd_init(argc, argv)) == NULL)
        _shttpd_elog(E_FATAL, NULL, "%s",
                     "Cannot initialize SHTTPD context");
	
    shttpd_register_uri(ctx, "/page1.html", &show_index, (void *) &data);
    shttpd_register_uri(ctx, "/page2.html", &show_index2, (void *)strBuf);
	

    _shttpd_elog(E_LOG, NULL, "shttpd %s started on port(s) %s, serving %s",
                 VERSION, ctx->options[OPT_PORTS], ctx->options[OPT_ROOT]);

    while (exit_flag == 0)
        shttpd_poll(ctx, 10 * 1000);

    _shttpd_elog(E_LOG, NULL, "Exit on signal %d", exit_flag);
    shttpd_fini(ctx);

    return (EXIT_SUCCESS);
}
