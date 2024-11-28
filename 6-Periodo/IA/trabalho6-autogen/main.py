import autogen

filter_criteria = {"model": ["phi"]}

config_list = autogen.config_list_from_json(
    "OAI_CONFIG_LIST.json",
    filter_dict=filter_criteria
)

# Configuration for the agents
llm_config = {"config_list": config_list, "cache_seed": 42, "temperature": 1}

# Define the two agents
husband = autogen.AssistantAgent(
    name="Husband",
    system_message="Talk in simple short phrases like a real conversation. Don't explain too much, keep your role. Role: \"You are a father of a family. You live in a small house. You meet your wife on the kitchen. You two are a bit stressed with each other because she spent her whole night taking care of the baby while you were sleeping because you were really tired of the work. You want to reconciliate.\"",
    llm_config=llm_config,
)

wife = autogen.AssistantAgent(
    name="Wife",
    system_message="Talk in simple short phrases like a real conversation. Don't explain too much, keep your role. Role: \"You are a mother of a family. You live in a small house. You meet your husband on the kitchen. You two are a bit stressed with each other because you spent your whole night taking care of the baby while he was sleeping. You want him to apologize.\"",
    llm_config=llm_config,
)

# Set up the group chat with the two agents
groupchat = autogen.GroupChat(
    agents=[husband, wife],
    allow_repeat_speaker=False,
    messages=[], 
    max_round=10  # Number of interaction rounds
)

# Create a GroupChatManager to manage the group chat
manager = autogen.GroupChatManager(
    groupchat=groupchat, 
    llm_config=llm_config
)

message="Hi honey. I'm sorry for last night."

# Start the interaction
husband.initiate_chat(
    recipient=wife,
    message=message,
    silent=False,
    # summary_args="Summarize takeaway from the conversation. Do not add any introductory phrases.",
    summary_method="reflection_with_llm"
)