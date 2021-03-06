import glob
import subprocess
import os
import shutil



test_folder    = './tests/'
result_folder  = './result/'
diff_folder    = './diffs/'

cmd_files       = sorted(glob.glob(test_folder + '*.txt'))
xml_files       = sorted(glob.glob(test_folder + '*.xml'))
expected_files  = sorted(glob.glob(test_folder + '*.out'))


if not os.path.exists(diff_folder):
    os.mkdir(diff_folder)


if not os.path.exists(result_folder):
    os.mkdir(result_folder)


print("\n\n\n\n{:=^{width}}".format(' Execution starts ', width = shutil.get_terminal_size().columns))

num_failures = 0

for test_num, (test_cmd, test_expected, test_xml) in enumerate(zip(cmd_files, expected_files, xml_files)):
    _, file_noext = os.path.split(test_cmd)

    result_path   = os.path.join(result_folder, file_noext +'.out')
    xml_path      = test_xml
    cmd_path      = test_cmd
    expected_path = test_expected
    diff_path     = diff_folder + file_noext + '.diff'

    run_command    = "./runner {} < {} > {}".format(xml_path, cmd_path, result_path)
    test_command   = "diff {} {}  > {}".format(result_path, expected_path, diff_path)



    try:
        print("\n\n\n{:=^{width}}".format( ' Test '+ str(test_num) + ' ', width = shutil.get_terminal_size().columns))
        print("Running " + run_command)
        subprocess.call([run_command], shell = True, timeout= 5)

        print("Testing output of {} on {}".format(test_cmd, test_xml))
        return_code = subprocess.call([test_command], shell=True, timeout=5)

        if return_code == 1:
            print("\n\n{:=^{width}}".format(' Test '+ str(test_num) + ' FAILED!! ', width = shutil.get_terminal_size().columns))
            print('diff FAILED for output {} of {}'.format(result_path, test_xml))
            num_failures += 1
            # exit(0)


    except subprocess.TimeoutExpired:
        print("Executing command file {} timed out, it took more than 5 secs. Fix that first!".format(test_cmd))
        exit(0)


if num_failures == 0:
    print("\n\n\n{:=^{width}}\n\n\n".format( ' All tests PASSED!! ',width = shutil.get_terminal_size().columns))

else:
    print("\n\n\n{:=^{width}}\n\n\n".format( ' {} tests PASSED and {} FAILED '.format(test_num + 1 - num_failures, num_failures),width = shutil.get_terminal_size().columns))




