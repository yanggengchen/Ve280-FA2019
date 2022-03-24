#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <string>
#include <cstdlib>
#include <cctype>
#include <cassert>
#include <algorithm>

#include "server_type.h"
#include "simulation.h"


using namespace std;


int main (int argc, char *argv[]) {
	string username, logfile;//names of files, Delete in linux
	string line;
	string user_path;

	User_t users[10] = {}; // change to 20
	User_t *pointer_users[10]; // change to 20
	int i = 0;

	//check mandatory inputs
	for (int i = 0; i < 10; i++) { //change into 20
		pointer_users[i] = &users[i];
	}

	try {
		if (argc < 3) {
			ostringstream oStream;
			oStream << "Error: Wrong number of arguments!" << endl;
			oStream << "Usage: ./p2 <username> <logfile>" << endl;
			throw Exception_t(INVALID_ARGUMENT, oStream.str());
		}
	}
	catch (Exception_t &exception) {
		cout << exception.error_info;
		//return 0;
	}

	//open files
	username = "username";
	logfile = "logfile";
	try {
		ifstream username_Stream(username);
		//check exception
		file_missing_error(&username_Stream, username);
		//read usernames and path
		getline(username_Stream, user_path);
		while (getline(username_Stream, line)) {
			users[i].username = line;
			i++;
		}
		//check capacity overflow exception
		if (i > MAX_USERS) {
			ostringstream oStream;
			oStream << "Error: Too many users!" << endl;
			oStream << "Maximal number of users is " << MAX_USERS << "." << endl;
			throw Exception_t(CAPACITY_OVERFLOW, oStream.str());
		}
		username_Stream.close();
	}
	catch (Exception_t &exception) {
		cout << exception.error_info;
		return 0;
	}
	
	//user initialization
	try {
		for (int j = 0; j < i; j++) {
			read_userinfo(&users[j], user_path, pointer_users);//read user_info
			read_userpost(&users[j], user_path, pointer_users);//read user's posts
		}
	}
	catch (Exception_t &exception) {
		cout << exception.error_info;
		return 0;
	}
	
	try{
		//logfile processing
		ifstream logfile_Stream(logfile);
		//check exception
		file_missing_error(&logfile_Stream,logfile);
		while (getline(logfile_Stream, line)) {
			istringstream request_Stream(line);
			string userA, command;
			request_Stream >> userA;
			if (userA == "trending") {
				int trending_number;
				request_Stream >> trending_number;
				trending(trending_number, pointer_users);
				continue;
			}
			request_Stream >> command;
			if (command == "follow") {
				string userB;
				request_Stream >> userB;
				follow(userA, userB, pointer_users);
				continue;
			}
			else if (command == "unfollow") {
				try {
					string userB;
					request_Stream >> userB;
					unfollow(userA, userB, pointer_users);
					continue;
				}
				catch (Exception_t &exception) {
					cout << exception.error_info;
				}
			}
			else if (command == "like") {
				try {
					string userB;
					int post_id;
					request_Stream >> userB >> post_id;
					like(userA, userB, post_id - 1, pointer_users);
					continue;
				}
				catch (Exception_t &exception) {
					cout << exception.error_info;
				}
			}
			else if (command == "unlike") {
				try {
					string userB;
					int post_id;
					request_Stream >> userB >> post_id;
					unlike(userA, userB, post_id - 1, pointer_users);
					continue;
				}
				catch (Exception_t &exception) {
					cout << exception.error_info;
				}
			}
			else if (command == "comment") {
				try {
					string userB, text;
					int post_id;
					request_Stream >> userB >> post_id;
					getline(logfile_Stream, text);
					comment(userA, userB, post_id - 1, text, pointer_users);
					continue;
				}
				catch (Exception_t &exception) {
					cout << exception.error_info;
				}
			}
			else if (command == "uncomment") {
				try {
					string userB;
					int post_id, comment_id;
					request_Stream >> userB >> post_id >> comment_id;
					uncomment(userA, userB, post_id - 1, comment_id - 1, pointer_users);
					continue;
				}
				catch (Exception_t &exception) {
					cout << exception.error_info;
				}
			}
			else if (command == "post") {
				cout << ">> post" << endl;
				int pos_userA = find_user(pointer_users, userA);
				int pos_post = users[pos_userA].num_posts;
				//read title
				getline(logfile_Stream, line);
				users[pos_userA].posts[pos_post].title = line;
				//read tags and text	
				while (getline(logfile_Stream, line)) {
					if (line.at(0) == '#') {
						int length = line.size();
						for (int j = 1; j < (length - 1); j++) {
							users[pos_userA].posts[pos_post].tags[users[pos_userA].posts[pos_post].num_tags] = users[pos_userA].posts[pos_post].tags[users[pos_userA].posts[pos_post].num_tags] + line.at(j);
						}
						users[pos_userA].posts[pos_post].num_tags++;
					}
					else {
						users[pos_userA].posts[pos_post].text = line;
						users[pos_userA].posts[pos_post].owner = &users[pos_userA];
						break;
					}
				}
				//other values
				users[pos_userA].num_posts++;
			}
			else if (command == "delete") {
				try {
					int post_id;
					request_Stream >> post_id;
					unpost(userA, post_id - 1, pointer_users);
					continue;
				}
				catch (Exception_t &exception) {
					cout << exception.error_info;
				}
			}
			else if (command == "refresh") {
				refresh(userA, pointer_users);
				continue;
			}
			else if (command == "visit") {
				string userB;
				request_Stream >> userB;
				visit(userA, userB, pointer_users);
				continue;
			}
		}
	}
	catch (Exception_t &exception) {
		cout << exception.error_info;
		return 0;
	}
	//ends
	return 0;
}
