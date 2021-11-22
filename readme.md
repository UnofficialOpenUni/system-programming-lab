<div align="center">
	<h1> HELLO AND WELCOME! </h1>
</div></br>

## The purpose of this repository:

The purpose of this repository is to provide students of the Open University a comfy platform to share, review, and draw new ideas and ispiration from each other's work of the System Programming Lab course various subjects, (such as solutions to exercises, solutions and testers to various course assignments, etc.)
</br>
<div align="center">
	<h2> Join our Social Media groups: </h2></br>
	<a href="https://discord.gg/SfHGVJ5s">
	<img src="https://discord.com/assets/cb48d2a8d4991281d7a6a95d2f58195e.svg" alt="Discord" height="80px" />
	</a>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;
	<a href="https://chat.whatsapp.com/FxptbDk4kgBJOleFaRTCHe">
	<img src="https://upload.wikimedia.org/wikipedia/commons/thumb/f/f7/WhatsApp_logo.svg/200px-WhatsApp_logo.svg.png" alt="Whatsapp" height="80px" />
	</a>
</div></br>

## Becoming a contributer:
Becoming a contributer will give you access to review and approve pull requests on the upstream repository, as well as pushing, merging and performing various different actions directly to the upstream repository wihtout needing to fork it and keeping your fork up to date.

If you are not new to Github and are certain in what you're doing and that you won't delete/modify other people's work by mistake, you are more than welcome to request becoming a contributer on `#request-git-access` on [our Discord 😃](https://discord.gg/SfHGVJ5s) </br>
We'd be more than happy to increase the amounts of contributors to this git repo as well as the amount of content uploaded for the benefit of all the students of this course.

## How to get started using this repo:

If you are new to this repository and are using it for the first time, here are a few simple steps to get you started:

### Copying the files from this repo to your PC:
1. Click the fork button on the top left corner of this webpage to fork this repository in your Github account.
2. Create a new folder on your PC to copy and save the files from the repository into.
3. Open the terminal, and navigate to the new folder you've just created. You can do this by using the `cd` command.</br></br>
	```
	### navigating into a folder: ###
	cd <Folder's name>/
	example:
	cd Desktop/

	### returning to the previous folder: ##
	cd ..

	### going back to the default folder (home/user) folder: ###
	cd
	```
4. Copy the files from the repository by using the command `git clone <url of the repository>`</br></br>
	```
	example:
	git clone https://github.com/**YOUR GITHUB USER NAME HERE**/system-programming-lab.git
	```
5. Create a new local branch on your name to review, edit, or add new files -  `git checkout -b <your name>` (the checkout command alone switches branches, the `-b` flag creates a new branch before switching to it):</br></br>
	```
	example:
	git checkout -b Moshe-Kozak
	
	### Worth to mention - if you wish to see a list of your existing branches type: ###
	git branch
	
	### To switch to a different branch without creating a new one, ommit the -b flag: ###
	git checkout name-of-branch

	### Deleting a branch: ###
	git branch -d name-of-branch-to-be-deleted
	```
6. If you wish to upload the changes you've made, you can review your changes using the `git status` command.
7. To add and commit the new changes use the `git add .` command followed by `git commit -m "A custom message describing the changes"`  and then use the command `git push origin <your branch name>`</br></br>
	```
	example:
	git add .
	git commit -m "Updated solutions for exercises from The C programming language - Chapter 6 (Moshe Kozak)"
	git push origin Moshe-Kozak
	```
8. The files should now appear on your forked Github repository under the new branch name. Open the repository on your web browser, and just under the "<> Code" tab, there should be a clickable button describing the branch you are currently seeing. If it says main, simply click it and choose the new branch you've just created.
9. There should now appear a green "New pull request" button on the top right corner of the screen. Click it, add your own custom message describing the updates which you wish to upload, and click create pull request.
10. Once your changes will be reviewed and approved by one of the Contributors of the repository, you will be able to see your new changes on the main branch of the upstream/original [UnofficialOpenUni's repository](https://github.com/UnofficialOpenUni/system-programming-lab.git).

### Keeping your forked repository and your PC files up to date:
1. Make sure your forked repository is up to date with the original (AKA upstream) repository by simply navigating to the "<> Code" tab on your repository's Github webpage, and click the "Fetch upstream > Fetch and Merge" button.
2. To update the repository's files saved to your PC, open the Terminal, and navigate to the repository's folder using the `cd` command.
3. Enter the command `git status` to make sure you are on the main branch of the git repository, otherwise, use the command</br> `git checkout main` to switch back to the main branch.
4. Enter the command `git pull origin main` - this will pull all the new changes and will update the files on your PC.


