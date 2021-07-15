sz = [4,4];
default_input_matrix = string(int32(rand(sz(1), sz(2)) * 200 - 100));
labelsv = string(1:sz(1));
labelsh = string(1:sz(2));
rep = x_mdialog('Enter a matrix',...
                 labelsv, labelsh, default_input_matrix)
