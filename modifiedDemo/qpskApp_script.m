% QPSKAPP_SCRIPT   Generate static library qpskApp from qpskApp.
% 
% Script generated from project 'qpskApp.prj' on 23-Jun-2021.
% 
% See also CODER, CODER.CONFIG, CODER.TYPEOF, CODEGEN.

%% Create configuration object of class 'coder.EmbeddedCodeConfig'.
cfg = coder.config('lib','coder',true);
cfg.TargetLang = 'C++';
cfg.GenerateReport = true;
cfg.ReportPotentialDifferences = false;
cfg.GenCodeOnly = true;
cfg.MaxIdLength = 1024;
cfg.CppInterfaceStyle = 'Methods';
cfg.CppInterfaceClassName = 'main';

%% Invoke MATLAB Coder.
codegen -config cfg qpskApp

