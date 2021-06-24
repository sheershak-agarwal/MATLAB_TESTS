% BUILD   Generate static library qpskApp from qpskApp.
% 
% Script generated from project 'qpskApp.prj' on 23-Jun-2021.
% 
% See also CODER, CODER.CONFIG, CODER.TYPEOF, CODEGEN.

%% Create configuration object of class 'coder.EmbeddedCodeConfig'.
cfg = coder.config('lib','ecoder',true);
cfg.GenerateReport = true;
cfg.ReportPotentialDifferences = false;
cfg.GenCodeOnly = true;

%% Invoke MATLAB Coder.
codegen -config cfg qpskApp

