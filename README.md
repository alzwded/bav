bav
===

store an archive of past, branched versions of a binary file

Tha plan
========

I need something to version and to branch out binary documents (or XML based in the case of abiword) without the overhead of a full repo (because I keep them on dropbox anyway).

What I need:
* be able to list milestones (date, check-in comment, document metadata)
* be able to revert at will
* be able to branch document out (merges will be done using tools specific to the binary format; e.g. MS word's built in document merging tool)
* store the stuff as DEFLATE to improve the coolness of the application (maybe switch to some binary-delta in the future, although I understand that was shot down for svn and git)
* be able to delete specific versions or entire branches

Specs
=====

Command line
------------

```
bav [command] [switches] file

commands:
init                    initialize *--.bav file
commit                  commit version
branch                  create/switch to branch
join                    splice a branch into the current one
revert                  revert working version to current checkout version
checkout                lock file for editing
release                 unlock file
log                     show log for current branch
delete                  remove a version forever

init:
<no options as of yet>

commit:
-m message              inline commit message

branch:
-d                      delete branch and all versions on it forever
-l                      list branches with number of commits
branch_name[:version]   name of the branch to be used/created with the offset version

join:
branch_name             the name of the branch to join into the current one

revert:
<no options as of yet>

checkout:
<no options as of yet>

release:
<no options as of yet>

log:
<no options as of yet>

delete:
<no options as of yet>
```

File format
-----------

```
1024KB current branch
       index block
     + 'v'
     + branch\n
     + version\n
     + date\n
     + message\n\n
     + size\n
     + file_offset\n
    || 'x'
     + file_offset
???B   raw DEFLATEd data
```

Arch
----

```
utils.c:
* load(f)
  + loads the index
* add(index_entry)
  + add a new entry to the index in the file
* remove(index_entry)
  + remove an index entry and associated data
* extract(index_entry, f)
  + extract a certain version of a file to the f stream
* write_file(f)
  + creates semaphore/temp file
  + truncates version file and redumps data
  + deletes semaphore/temp file

<command_name>.c
* implementation of each command
```
