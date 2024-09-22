echo "*****************************************"
echo "Commit and push all files into repository"
echo "*****************************************"

DATE=$(date +'%d.%m.20%y %T')
comment=${1:?"A checkin comment must be specified (The current date and time is automatically added)."}

# git remote add origin https://github.com/Holger2020/Arduino.git
# git branch -M main

echo "------------------------------------------------"
echo "Get the current status:"
echo "------------------------------------------------"
git status

echo "------------------------------------------------"
echo "Add all new files:"
echo "------------------------------------------------"
git add -A

echo "------------------------------------------------"
echo "Commit new/modified files to remote repository:"
echo "------------------------------------------------"
git commit -m "$DATE ${1}" 
# git push -u origin main
git push 

echo "------------------------------------------------"
echo "Pulling files from remote repository:"
echo "------------------------------------------------"
git pull --ff-only
