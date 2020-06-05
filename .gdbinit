#!gdb

define setup
  break sc_main 
  break parse_command_line 
  break inject_summary 
  break inject_errors 
  break Basic_top::Basic_top
  break Basic_top::before_end_of_elaboration
  break Basic_top::end_of_elaboration
  break Basic_top::start_of_simulation
  break Basic_top::end_of_simulation
  break Basic_top::Basic_thread
end

define test
  set args -when $arg0 -inject warning -inject error -inject fatal
end

define test0
  set args -test
end

define test1
  test elaboration
end

define test2
  test before_end_of_elaboration
end

define test3
  test end_of_elaboration
end

define test4
  test start_of_simulation
end

define test5
  test running
end

define test6
  test end_of_simulation
end

define test7
  test stopped
end

define test8
  test paused
end
