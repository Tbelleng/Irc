#ifndef CHANNEL_HPP
# define CHANNEL_HPP

class Channel
{
  private:
  
	std::vector<int> _members;
	std::vector<int> _opMembers;
	std::string _name;
	Topic _topic;

  public:

    Channel(int opMember);
	Channel(std::string name, int _opMember);
	~Channel(void);
	//void sendTo(User &sender, const std::string message);
	//void sendToChannel(User &sender, std::vector<std::string> buffers);
	void                setMember(int newMember);
    void                setOpMember(int oldOpMember, int newOpMember);
    void                setGrade(int Member, int grade);
    bool                setTopic(int Member, std::string topic);

	std::string getName( void ) const
	{
        return this->_name;
	}

	std::vector<int> getAllOpMember(void) const
	{
        return this->_opMembers;
	}

	std::string getTopic(void) const {
    // Channel::sendMessage(this->_topic.getTopic().c_str());
        return (this->_topic.getTopic());
	}
	
	std::vector<int> getAllMember( void ) const
	{
        return this->_members;
	}

	bool isInChannel(User &sender);

	std::string vectorToString(const std::vector<std::string> &strVector);

    void                suppMember(int opMember, int suppMember);
    void                suppOpMember(int opMember, int suppOpMember);
    void                memberLeave(int leaver);

    void                 sendMessage(const char* message) const;

	bool                isInChannel(int user);

};

#endif
// #ifndef CHANNEL_HPP
// # define CHANNEL_HPP

// class Channel
// {
//   private:
// 	std::vector<std::string> _members;
// 	std::vector<std::string> _opMembers;
// 	std::string _name;
// 	Topic _topic;

//   public:
// 	Channel(User &sender, std::string channel_name);
// 	~Channel(void);
// 	void sendTo(User &sender, const std::string message);
// 	void (User &sender, std::vector<std::string> buffers);

// 	std::string getChannelName(void);
// 	const std::vector<std::string> &getChannelOp(void)
// 	{
// 		return (_opMembers);
// 	}

// 	const std::vector<std::string> &getChannelMembers(void)
// 	{
// 		return (_members);
// 	}

// 	bool isInChannel(User &sender);
// };

// std::string vectorToString(const std::vector<std::string> &strVector);

// #endif
