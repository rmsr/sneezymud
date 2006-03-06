#ifndef __SESSION_CGI_H
#define __SESSION_CGI_H

#include <cgicc/Cgicc.h>

// TODO:
// check for duplicates before trying to use a session id
// add option for persistent logins rather than current-session


// TSession is a class for handling session authentication in cgi
// scripts.  The idea is that the user can login using their sneezy
// account name and password, and we give them a cookie that we can
// check later for authentication.

// Usage:
//
// Cgicc cgi;
// TSession session(cgi, "mudmail");
//
// if(!session.isValid()){
//   // send them to a login form, and when you get a name and password:
//   if(session.checkPasswd(name, passwd)){
//     session.createSession(60*60); // 1 hour duration
//     cout<< HTTPRedirectHeader("mudmail.cgi").setCookie(session.getCookie());
//   } else {
//     // bad login
//   }
// } else {
//   // they are logged in
// }


class TSession {
  sstring session_id;
  int account_id;

  sstring cookiename;
  int cookieduration;

  // probably a better way to deal with this cgi stuff but I'm too lazy to
  // figure it out.  we use it in this class to get the cookie info.
  // trying to store it as a non-pointer variable causes runtime errors.
  cgicc::Cgicc *cgi;

  // uses the cgicc object to find the cookie and returns the session id
  sstring getSessionCookie();
  // generates a hopefully unguessable session id string.
  sstring generateSessionID();
  // pulls out the account id that is associated with the stored session id
  // returns -1 if no account id is found (ie session id is invalid)
  int validateSessionID();

public:
  // creates a new session id string and inserts/replaces it into the database
  // duration is both the cookie expiration and time duration saved in db
  void createSession(int duration);

  // returns false if there is no session id or account id set in the class
  bool isValid();
  // deletes the session id string from the database
  void logout();

  // validates name and passwd, user input.
  bool checkPasswd(sstring name, sstring passwd);

  cgicc::HTTPCookie getCookie();

  int getAccountID(){ return account_id; }
  sstring getSessionID(){ return session_id; }

  TSession(cgicc::Cgicc, sstring);
};

#endif
