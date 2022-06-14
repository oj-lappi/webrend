#!/bin/sh

dev_dir=PROJECT_DIRECTORY

CXX_DEVELOPER_UID=$(stat --printf="%u" ${dev_dir})
CXX_DEVELOPER_GID=$(stat --printf="%g" ${dev_dir})

# dev-group != user group
if [ "${CXX_DEVELOPER_GID}" != "${CXX_DEVELOPER_UID}" ];then
    getent group ${CXX_DEVELOPER_GID} || groupadd -g ${CXX_DEVELOPER_GID} cxx-development-group
    useradd -m -s /bin/bash -u ${CXX_DEVELOPER_UID} -G cxx-development-group cxx-developer
else
    useradd -m -s /bin/bash -u ${CXX_DEVELOPER_UID} cxx-developer
fi

#Set up the home directory of cxx-developer
#This first line reports that cp won't create hard links
#	cp: will not create hard link '/home/cxx-developer/dotfiles' to directory '/home/cxx-developer/.'
#BUG: we should loop through the files in dotfiles and create a link for each instead
cp -r /developer_home/dotfiles/.* /home/cxx-developer
cp -r /developer_home/config /home/cxx-developer/.config
cp -r /developer_home/local /home/cxx-developer/.local

#chown the home directory, root takes ownership otherwise
chown -R cxx-developer /home/cxx-developer

su --login cxx-developer -c "cd ${dev_dir}; pre-commit install --install-hooks"

touch /home/cxx-developer/user_created

# I think this can be anything, as long as the container stays alive
exec /bin/bash
