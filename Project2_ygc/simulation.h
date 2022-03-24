/*
 * This is VE280 Project 2, SU2020.
 * Written by Ziqiao Ma and Zhuoer Zhu.
 * Latest Update: 5/29/2020.
 * All rights reserved.
 */

#include "server_type.h"

// TODO: Declare your functions in this header file.
// Hint: You may need these request handling functions.

void visit(string userA, string userB, User_t* user[]);
void trending(int number, User_t* user[]);
void refresh(string userA, User_t* user[]);
void follow(string userA, string userB, User_t* user[]);
void unfollow(string userA, string userB, User_t* user[]);
void like(string userA, string userB, int post_id, User_t* user[]);
void unlike(string userA, string userB, int post_id, User_t* user[]);
void comment(string userA, string userB, int post_id, string text, User_t* user[]);
void uncomment(string userA, string userB, int post_id, int comment_id, User_t* user[]);
void unpost(string userA, int post_id, User_t* user[]);

void read_userinfo(User_t* user, string path, User_t* alluser[]);
void read_userpost(User_t* user, string path, User_t* alluser[]);

/* Helper Functions */

bool compare(Tag_t a, Tag_t b);
int find_user(User_t* user[], string username);
void capacity_overflow_error(string element, string object, string object_name, int current_num, const int Max);
void file_missing_error(istream* Stream, string file);

// Printing

void printUser(User_t& user, const string& relationship);
void printPost(Post_t& post);
void printTag(const Tag_t& tag, unsigned int rank);

