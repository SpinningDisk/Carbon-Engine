import re

sample = "Hans.Peter.v1.x = 1.1, 2.2"
token = r"\.([^\b\.\s=,]*)"

fuck = re.compile(token)
print(fuck.findall(sample))
exit(1)
print(match_object.group())