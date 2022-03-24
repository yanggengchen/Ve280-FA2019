/*
 * This is VE280 Project 2, SU2020.
 * Written by Ziqiao Ma and Zhuoer Zhu.
 * Latest Update: 5/29/2020.
 * All rights reserved.
 */
#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <string>
#include <cstdlib>
#include <cctype>
#include <cassert>
#include <algorithm>
#include "simulation.h"

using namespace std;
// TODO: Define your functions in this header file.

/* Helper Functions */
bool compare(Tag_t a, Tag_t b) {
	if (a.tag_score != b.tag_score) return (a.tag_score > b.tag_score);
	else return (a.tag_content > b.tag_content);
}

int find_user(User_t* user[], string username) {
	int pos_user = 21;
	for (int i = 0; i < 10; i++) { //change to MAX
		if (user[i]->username == username) {
			pos_user = i;
			return pos_user;
		}
	}
	return 0;
}

void capacity_overflow_error(string element, string object, string object_name, int current_num, const int Max) {
	if (current_num > Max) {
		ostringstream oStream;
		oStream << "Error: Too many " << element << " for " << object << " " << object_name << "!" << endl;
		oStream << "Maximal number of " << element << " is " << Max << "." << endl;
		throw Exception_t(CAPACITY_OVERFLOW, oStream.str());
	}
}

void file_missing_error(istream* Stream, string file) {
	if (!*Stream) {
		ostringstream oStream;
		oStream << "Error: Cannot open file " << file << "!" << endl;
		throw Exception_t(FILE_MISSING, oStream.str());
	}
}

//Initialization functions
void read_userinfo(User_t* user, string path, User_t* alluser[]) {
	//open file
	char get_endline;
	ifstream userinfo_Stream(path + "/" + user->username + "/user_info");
	//check exception
	file_missing_error(&userinfo_Stream, path + "/" + user->username + "/user_info");
	//read number of posts
	userinfo_Stream >> user->num_posts;
	userinfo_Stream.get(get_endline);
	//check exception
	capacity_overflow_error("posts", "user", user->username, user->num_posts, MAX_POSTS);
	//read number of following
	userinfo_Stream >> user->num_following;
	userinfo_Stream.get(get_endline);
	//check exception
	capacity_overflow_error("followings", "user", user->username, user->num_following, MAX_FOLLOWING);
	for (int i = 0; i < (int)user->num_following; i++) {
		string username;
		userinfo_Stream >> username;
		for (int j = 0; j < 10 /*change into MAX in linux*/; j++) {
			if (alluser[j]->username == username) {
				user->following[i] = alluser[j];
				break;
			}
		}
		userinfo_Stream.get(get_endline);
	}
	//read number of followers
	userinfo_Stream >> user->num_followers;
	userinfo_Stream.get(get_endline);
	//check exception
	capacity_overflow_error("followers", "user", user->username, user->num_followers, MAX_FOLLOWERS);
	for (int i = 0; i < (int)user->num_followers; i++) {
		string username;
		userinfo_Stream >> username;
		for (int l = 0; l < 10 /*change into MAX in linux*/; l++) {
			if (alluser[l]->username == username) {
				user->follower[i] = alluser[l];
				break;
			}
		}
		userinfo_Stream.get(get_endline);
	}

	//close file
	userinfo_Stream.close();
}

void read_userpost(User_t* user, string path, User_t* alluser[]) {
	char get_endline;

	//open files
	for (int i = 0; i < (int)user->num_posts; i++) {
		string number = to_string(i + 1);
		ifstream userpost_Stream(path + "/" + user->username + "/posts/" + number);
		//check exception
		file_missing_error(&userpost_Stream, path + "/" + user->username + "/posts/" + number);
		//read title
		string line;
		getline(userpost_Stream, line);
		user->posts[i].title = line;
		//read tags and text	
		while (getline(userpost_Stream, line)) {
			if (line.at(0) == '#') {
				int length = line.size();
				int repeat_flag = 0;
				for (int j = 1; j < (length - 1); j++) {
					user->posts[i].tags[user->posts[i].num_tags] = user->posts[i].tags[user->posts[i].num_tags] + line.at(j);
				}
				for (int j = 0; j < (int)user->posts[i].num_tags; j++) {
					if (user->posts[i].tags[user->posts[i].num_tags] == user->posts[i].tags[j]) {
						user->posts[i].tags[user->posts[i].num_tags] = "";
						repeat_flag = 1;
					}
				}
				if (repeat_flag == 0)
					user->posts[i].num_tags++;
				//check exception
				capacity_overflow_error("tags", "post", user->posts[i].title, user->posts[i].num_tags, MAX_TAGS);
			}
			else {
				user->posts[i].text = line;
				break;
			}
		}
		//read likes
		userpost_Stream >> user->posts[i].num_likes;
		userpost_Stream.get(get_endline);
		//check exception
		capacity_overflow_error("likes", "post", user->posts[i].title, user->posts[i].num_likes, MAX_LIKES);
		for (int j = 0; j < (int)user->posts[i].num_likes; j++) {
			string username;
			getline(userpost_Stream, username);
			for (int k = 0; k < 10; k++) { // change to 20
				if (alluser[k]->username == username) {
					user->posts[i].like_users[j] = alluser[k];
					break;
				}
			}
		}
		//read comments
		userpost_Stream >> user->posts[i].num_comments;
		userpost_Stream.get(get_endline);
		//check exception
		capacity_overflow_error("comments", "post", user->posts[i].title,user->posts[i].num_comments, MAX_COMMENTS);
		for (int j = 0; j < (int)user->posts[i].num_comments; j++) {
			string username;
			getline(userpost_Stream, username);
			for (int k = 0; k < 10; k++) { // change to 20
				if (alluser[k]->username == username) {
					user->posts[i].comments[j].user = alluser[k];
					getline(userpost_Stream, line);
					user->posts[i].comments[j].text = line;
					break;
				}
			}
		}
		user->posts[i].owner = user;
	}
}

//Processing functions
void trending(int number, User_t* user[]) {
	cout << ">> trending" << endl;
	//find all tags and their score
	Tag_t Alltags[500] = {};
	int num_tags = 0;
	bool find_flag = 0;
	for (int i = 0; i < 10; i++) { // change to MAX
		for (int j = 0; j < (int)user[i]->num_posts; j++) {
			for (int k = 0; k < (int)user[i]->posts[j].num_tags; k++) {
				for (int l = 0; l < num_tags; l++) {
					if (user[i]->posts[j].tags[k] == Alltags[l].tag_content) {
						Alltags[l].tag_score = Alltags[l].tag_score + 5 + (int)user[i]->posts[j].num_likes + 3 * (int)user[i]->posts[j].num_comments;
						find_flag = 1;
						break;
					}
				}
				if (find_flag == 0) {
					Alltags[num_tags].tag_content = user[i]->posts[j].tags[k];
					Alltags[num_tags].tag_score = Alltags[num_tags].tag_score + 5 + (int)user[i]->posts[j].num_likes + 3 * (int)user[i]->posts[j].num_comments;
					num_tags++;
				}
				find_flag = 0;
			}
		}
	}
	//sort the tags according to score
	sort(Alltags, Alltags + num_tags, compare);
	//print the first number tags
	if (num_tags >= number) {
		for (int i = 0; i < number; i++) {
			printTag(Alltags[i], i + 1);
		}
	}
	else {
		for (int i = 0; i < num_tags; i++) {
			printTag(Alltags[i], i + 1);
		}
	}
	
}

void follow(string userA, string userB, User_t * user[]) {
	cout << ">> follow" << endl;
	//find positions of userA and userB
	int pos_userA = find_user(user, userA);
	int pos_userB = find_user(user, userB);
	//check if A has already followed B
	int follow_flag = 0;
	for (int i = 0; i < user[pos_userA]->num_following; i++) {
		if (user[pos_userA]->following[i] == user[pos_userB]) {
			follow_flag = 1;
			break;
		}
	}
	if (follow_flag == 0)
	{
		//add userB into userA's following list
		user[pos_userA]->following[user[pos_userA]->num_following] = user[pos_userB];
		user[pos_userA]->num_following++;
		//add userA into userB's follower's list
		user[pos_userB]->follower[user[pos_userB]->num_followers] = user[pos_userA];
		user[pos_userB]->num_followers++;
	}
}

void unfollow(string userA, string userB, User_t * user[]) {
	cout << ">> unfollow" << endl;
	//find positions of userA and userB
	int pos_userA = find_user(user, userA);
	int pos_userB = find_user(user, userB);
	//check if A has already followed B
	int follow_flag = 0;
	for (int i = 0; i < user[pos_userA]->num_following; i++) {
		if (user[pos_userA]->following[i] == user[pos_userB]) {
			follow_flag = 1;
			break;
		}
	}
	if (follow_flag == 0) {
		stringstream oStream;
		oStream << "Error: " << user[pos_userA]->username << " cannot like unfollow " << user[pos_userB]->username << "!" << endl;
		oStream << user[pos_userA]->username << " has not followed " << user[pos_userB]->username << "." << endl;
		throw Exception_t(INVALID_LOG, oStream.str());
	}
	//erase userB in userA's following list
	for (int i = 0; i < (int)user[pos_userA]->num_following; i++) {
		if (user[pos_userA]->following[i]->username == userB) {
			for (int j = i; j < (int)user[pos_userA]->num_following; j++) {
				user[pos_userA]->following[j] = user[pos_userA]->following[j + 1];
			}
		}
	}
	user[pos_userA]->num_following--;
	//erase userA in userB's follower's list
	for (int i = 0; i < (int)user[pos_userB]->num_followers; i++) {
		if (user[pos_userB]->follower[i]->username == userA) {
			for (int j = i; j < (int)user[pos_userB]->num_followers; j++) {
				user[pos_userB]->follower[j] = user[pos_userB]->follower[j + 1];
			}
		}
	}
	user[pos_userB]->num_followers--;
}

void like(string userA, string userB, int post_id, User_t* user[]) {
	cout << ">> like" << endl;
	//find userA and userB
	int pos_userA = find_user(user, userA);
	int pos_userB = find_user(user, userB);
	//check whether userB had posted post_id
	if (user[pos_userB]->num_posts < post_id + 1) {
		ostringstream oStream;
		oStream << "Error: " << user[pos_userA]->username << " cannot like post #" << post_id + 1 << " of " << user[pos_userB]->username << "!" << endl;
		oStream << user[pos_userB]->username << " does not have post #" << post_id + 1 << "." << endl;
		throw Exception_t(INVALID_LOG, oStream.str());
	}
	//check whether userA already liked the post
	for (int i = 0; i < user[pos_userB]->posts[post_id].num_likes; i++) {
		if (user[pos_userB]->posts[post_id].like_users[i]->username == userA) {
			stringstream oStream;
			oStream << "Error: " << user[pos_userA]->username << " cannot like post #" << post_id + 1 << " of " << user[pos_userB]->username << "!" << endl;
			oStream << user[pos_userA]->username << " has already liked post #" << post_id + 1 << " of " << user[pos_userB]->username << "." << endl;
			throw Exception_t(INVALID_LOG, oStream.str());
		}
	}
	//add userA to list of userB
	user[pos_userB]->posts[post_id].like_users[user[pos_userB]->posts[post_id].num_likes] = user[pos_userA];
	user[pos_userB]->posts[post_id].num_likes++;
}

void unlike(string userA, string userB, int post_id, User_t* user[]) {
	cout << ">> unlike" << endl;
	//find userA and userB
	int pos_userA = find_user(user, userA);
	int pos_userB = find_user(user, userB);
	//check whether userB had posted post_id
	if (user[pos_userB]->num_posts < post_id + 1) {
		ostringstream oStream;
		oStream << "Error: " << user[pos_userA]->username << " cannot unlike post #" << post_id + 1 << " of " << user[pos_userB]->username << "!" << endl;
		oStream << user[pos_userB]->username << " does not have post #" << post_id + 1 << "." << endl;
		throw Exception_t(INVALID_LOG, oStream.str());
	}
	//check whether userA already liked the post
	bool like_flag = 0;
	for (int i = 0; i < user[pos_userB]->posts[post_id].num_likes; i++) {
		if (user[pos_userB]->posts[post_id].like_users[i]->username == userA)
			like_flag = 1;
	}
	if (like_flag == 0) {
		stringstream oStream;
		oStream << "Error: " << user[pos_userA]->username << " cannot unlike post #" << post_id + 1 << " of " << user[pos_userB]->username << "!" << endl;
		oStream << user[pos_userA]->username << " has not liked post #" << post_id + 1 << " of " << user[pos_userB]->username << "." << endl;
		throw Exception_t(INVALID_LOG, oStream.str());
	}
	//erase userA from like_list of userB
	for (int i = 0; i < (int)user[pos_userB]->posts[post_id].num_likes; i++) {
		if (user[pos_userB]->posts[post_id].like_users[i]->username == userA) {
			for (int j = i; j < (int)user[pos_userB]->posts[post_id].num_likes; j++) {
				user[pos_userB]->posts[post_id].like_users[j] = user[pos_userB]->posts[post_id].like_users[j + 1];
			}
		}
	}
	user[pos_userB]->posts[post_id].num_likes--;
}

void comment(string userA, string userB, int post_id, string text, User_t* user[]) {
	cout << ">> comment" << endl;
	//find positions of userA and userB
	int pos_userA = find_user(user, userA);
	int pos_userB = find_user(user, userB);
	//check whether userB had posted post_id
	if (user[pos_userB]->num_posts < post_id + 1) {
		ostringstream oStream;
		oStream << "Error: " << user[pos_userA]->username << " cannot comment post #" << post_id + 1 << " of " << user[pos_userB]->username << "!" << endl;
		oStream << user[pos_userB]->username << " does not have post #" << post_id + 1 << "." << endl;
		throw Exception_t(INVALID_LOG, oStream.str());
	}
	//add comment
	user[pos_userB]->posts[post_id].comments[user[pos_userB]->posts[post_id].num_comments].user = user[pos_userA];
	user[pos_userB]->posts[post_id].comments[user[pos_userB]->posts[post_id].num_comments].text = text;
	user[pos_userB]->posts[post_id].num_comments++;
}

void uncomment(string userA, string userB, int post_id, int comment_id, User_t* user[]) {
	cout << ">> uncomment" << endl;
	//find positions of userA and userB
	int pos_userA = find_user(user, userA);
	int pos_userB = find_user(user, userB);
	//check whether userB had posted post_id
	if (user[pos_userB]->num_posts < post_id + 1) {
		ostringstream oStream;
		oStream << "Error: " << user[pos_userA]->username << " cannot uncomment comment #" << comment_id + 1 << " of post #" << post_id + 1 << " posted by " << user[pos_userB]->username << "!" << endl;
		oStream << user[pos_userB]->username << " does not have post #" << post_id + 1 << "." << endl;
		throw Exception_t(INVALID_LOG, oStream.str());
	}
	//check whether post post_id of userB has comment_id
	if (user[pos_userB]->posts[post_id].num_comments < comment_id + 1) {
		ostringstream oStream;
		oStream << "Error: " << user[pos_userA]->username << " cannot uncomment comment #" << comment_id + 1 << " of post #" << post_id + 1 << " posted by " << user[pos_userB]->username << "!" << endl;
		oStream << "Post #" << post_id + 1 << " does not have comment #" << comment_id + 1 << "." << endl;
		throw Exception_t(INVALID_LOG, oStream.str());
	}
	//check whether userA is owner of comment_id of post_id of userB
	if (user[pos_userB]->posts[post_id].comments[comment_id].user->username != userA) {
		ostringstream oStream;
		oStream << "Error: " << user[pos_userA]->username << " cannot uncomment comment #" << comment_id + 1 << " of post #" << post_id + 1 << " posted by " << user[pos_userB]->username << "!" << endl;
		oStream << user[pos_userA]->username << " is not the owner of comment #" << comment_id + 1 << "." << endl;
		throw Exception_t(INVALID_LOG, oStream.str());
	}
	//delete comment
	for (int j = comment_id; j < (int)user[pos_userB]->posts[post_id].num_comments; j++) {
		user[pos_userB]->posts[post_id].comments[j] = user[pos_userB]->posts[post_id].comments[j + 1];
	}
	user[pos_userB]->posts[post_id].num_comments--;
}

void unpost(string userA, int post_id, User_t* user[]) {
	cout << ">> delete" << endl;
	//find position of userA
	int pos_userA = find_user(user, userA);
	//check whether userA has posted post_id
	if (user[pos_userA]->num_posts < post_id + 1) {
		ostringstream oStream;
		oStream << "Error: " << user[pos_userA]->username << " cannot delete post #" << post_id + 1 << "!" << endl;
		oStream << user[pos_userA]->username << " does not have post #" << post_id + 1 << "." << endl;
		throw Exception_t(INVALID_LOG, oStream.str());
	}
	//delete post[post_id]
	for (int i = post_id; i < (int)user[pos_userA]->num_posts; i++) {
		user[pos_userA]->posts[post_id] = user[pos_userA]->posts[post_id + 1];
	}
	user[pos_userA]->num_posts--;
}

void refresh(string userA, User_t* user[]) {
	cout << ">> refresh" << endl;
	//find userA
	int pos_userA = find_user(user, userA);

	//print userA's own posts
	for (int i = 0; i < (int)user[pos_userA]->num_posts; i++) {
		printPost(user[pos_userA]->posts[i]);
	}

	//print post userA is following
	for (int i = 0; i < (int)user[pos_userA]->num_following; i++) {
		for (int j = 0; j < (int)user[pos_userA]->following[i]->num_posts; j++) {
			printPost(user[pos_userA]->following[i]->posts[j]);
		}
	}
}

void visit(string userA, string userB, User_t* user[]) {
	cout << ">> visit" << endl;
	//find positions of userA and userB
	int pos_userA = find_user(user, userA);
	int pos_userB = find_user(user, userB);

	//relationship between userA and userB
	bool A_follow_B = 0;
	bool B_follow_A = 0;
	string relationship = "";
	if (user[pos_userA] == user[pos_userB]) {
		relationship = "";
	}
	for (int i = 0; i < (int)user[pos_userA]->num_following; i++) {
		if (user[pos_userA]->following[i] == user[pos_userB]) {
			A_follow_B = 1;
		}
	}
	for (int i = 0; i < (int)user[pos_userB]->num_following; i++) {
		if (user[pos_userB]->following[i] == user[pos_userA]) {
			B_follow_A = 1;
		}
	}
	if (A_follow_B == 1) {
		if (B_follow_A == 1) {
			relationship = "friend";
		}
		else relationship = "following";
	}
	else relationship = "stranger";

	//print
	printUser(*user[pos_userB], relationship);
}

// Printing

void printUser(User_t& user, const string& relationship){
    cout << user.username << endl;
    cout << relationship << endl;
    cout << "Followers: " << user.num_followers
         << "\nFollowing: " << user.num_following << endl;
}


void printPost(Post_t& post) {
	cout << post.owner->username << endl;
	cout << post.title << endl;
	cout << post.text << endl;
	cout << "Tags: ";
	for (unsigned int i = 0; i < post.num_tags; ++i) {
		cout << post.tags[i] << " ";
	}
	cout << "\nLikes: " << post.num_likes << endl;
	if (post.num_comments > 0) {
		cout << "Comments:" << endl;
		for (unsigned int i = 0; i < post.num_comments; ++i) {
			cout << post.comments[i].user->username << ": "
				<< post.comments[i].text << endl;
		}
	}
	cout << "- - - - - - - - - - - - - - -" << endl;
}


void printTag(const Tag_t& tag, unsigned int rank){
    cout << rank << " " << tag.tag_content << ": " << tag.tag_score << endl;
}
