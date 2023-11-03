#ifndef CHANNEL_HPP
# define CHANNEL_HPP

class Channel
{
  private:
  
	std::vector<std::string> _members;
	std::vector<std::string> _opMembers;
	std::string _name;
	std::string _topic;
	std::string _password;
	bool _needPass;

  public:

    Channel(std::string name, std::string topic, std::string username);
	~Channel(void);

	void                setMember(int newMember);
    void                setOpMember(int oldOpMember, int newOpMember);
    void                setGrade(int Member, int grade);
    bool                setTopic(int Member, std::string topic);

	std::string getName( void ) const
	{
        return this->_name;
	}

	bool isInChannel(User &sender);
	
	void   broadcasting(int sender, std::string message);

	void                addMember(User& client);
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
