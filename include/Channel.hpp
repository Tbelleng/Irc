#ifndef CHANNEL_HPP
# define CHANNEL_HPP

class Channel
{
  private:
	std::vector<std::string> _members;
	std::vector<std::string> _opMembers;
	std::string _name;
	Topic _topic;

  public:
	Channel(User &sender, std::string channel_name);
	~Channel(void);
	void sendTo(User &sender, const std::string message);
	void sendToChannel(User &sender, std::vector<std::string> buffers);

	std::string getChannelName(void);
	const std::vector<std::string> &getChannelOp(void)
	{
		return (_opMembers);
	}

	const std::vector<std::string> &getChannelMembers(void)
	{
		return (_members);
	}

	bool isInChannel(User &sender);
};

std::string vectorToString(const std::vector<std::string> &strVector);

#endif