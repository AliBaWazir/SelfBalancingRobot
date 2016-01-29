% Tracking of x command
req1 = TuningGoal.Tracking('xref','x',3);

% Rejection of impulse disturbance dF
Qxu = diag([16 1 0.01]);
req2 = TuningGoal.LQG('dF',{'Theta','x','F'},1,Qxu);

% Stability margins
req3 = TuningGoal.Margins('F',6,40);

% Pole locations
MinDamping = 0.5;
MaxFrequency = 45;
req4 = TuningGoal.Poles(0,MinDamping,MaxFrequency);

ST0 = slTuner('inverted_pendulum',{'Position Controller','Angle Controller'});
addPoint(ST0,'F');

rng(0)
Options = systuneOptions('RandomStart',5);
[ST, fSoft] = systune(ST0,[req1,req2],[req3,req4],Options);

% Validation
figure('Position',[100   100   575   660]);
viewSpec([req1,req3,req4],ST)


T = getIOTransfer(ST,{'xref','dF'},{'x','Theta'});
figure('Position',[100   100   650   420]);
subplot(121), step(T(:,1),10)
title('Tracking of set point change in position')
subplot(122), impulse(T(:,2),10)
title('Rejection of impulse disturbance')

C1 = getBlockValue(ST,'Position Controller')

C2 = zpk(getBlockValue(ST,'Angle Controller'))

%root locus
L = getLoopTransfer(ST,'F',-1);
figure;
rlocus(L)
set(gca,'XLim',[-25 20],'YLim',[-20 20])

writeBlockValue(ST)