/*
 * This is VE280 Project 2, SU2020.
 * Written by Ziqiao Ma and Zhuoer Zhu.
 * Latest Update: 5/29/2020.
 * All rights reserved.
 */

#include "server_type.h"

// TODO: Declare your functions in this header file.
// Hint: You may need these request handling functions.


void visit(User_t user[], string user1, string user2, unsigned int usernum);
void trending(User_t user[],unsigned int trendn, unsigned int usernum);
void refresh(User_t user[], string user1, unsigned int usernum);
void follow(User_t user[], string user1, string user2, unsigned int usernum);
void unfollow(User_t user[], string user1, string user2, unsigned int usernum);
void like(User_t user[], string user1, string user2, unsigned int postid, unsigned int usernum);
void unlike(User_t user[], string user1, string user2, unsigned int postid, unsigned int usernum);
void comment(User_t user[], string user1, string user2, unsigned int postid, string text, unsigned int usernum);
void uncomment(User_t user[], string user1, string user2, unsigned int postid, unsigned int commentid, unsigned int usernum);
void post(ifstream* logfile, User_t user[], string user1, unsigned int usernum);
void unpost(User_t user[], string user1, unsigned int postid, unsigned int usernum);


/* Helper Functions */

// Printing
void printUser(User_t& user, const string& relationship);
void printPost(Post_t& post);
void printTag(const Tag_t& tag, unsigned int rank);

