# See following articles for detail:
# - https://help.github.com/articles/configuring-a-remote-for-a-fork/
# - https://help.github.com/articles/syncing-a-fork/"

git fetch upstream
git checkout master
git merge upstream/master
