#ifndef CHANNEL_HPP
# define CHANNEL_HPP

class Channel
{
  private:
  
	std::vector<std::string> _members;
	std::vector<std::string> _opMembers;
	std::vector<int> _usersFd;
	std::string _name;
	std::string _topic;
	std::string _password;
	unsigned int _maxUsers;
	unsigned int _currentUsers;
	bool _needPass;
	bool _onlyInvite;

  public:

    Channel(std::string name, std::string username, std::string pass, User& client);
	~Channel(void);

	void                setMember(int newMember);
    void                setOpMember(int oldOpMember, int newOpMember);
    void                setGrade(int Member, int grade);
    bool                setTopic(int Member, std::string topic);

	std::string getName(void) const
	{
        return this->_name;
	}

	std::string                getTopic(void);
	std::string                getPassword(void);
	bool                       needPass(void);
	unsigned int               getMaxUsers(void);
	unsigned int               getCurrentUsers(void);
	void                       addMember(User& client);
	void                       increaseCurrentUser(void);
	std::string                getUserList(void);
	void                       joinBroadcast(User& sender);
	void                       broadcasting(std::string msg, int sender_fd);
	
	
	
    void                suppMember(int opMember, int suppMember);
    void                suppOpMember(int opMember, int suppOpMember);
    void                memberLeave(int leaver);

	void                spreadMsg(User& sender, std::string channe_name, std::vector<std::string> message);
    void                sendMessage(const char* message) const;
    int                 getSpecificMember(void);

	bool                isInChannel(int user);

};

std::string vectorToString(const std::vector<std::string> &strVector);

#endif
