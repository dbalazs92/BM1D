#include "Draw2D.hh"


Draw2D::Draw2D(int nop, double percent, int nRunsp, std::vector<Double_t> tp, std::vector<Double_t> xp, int nThreads_) //int nop, double percent, int nRunsp, std::vector<Double_t> tp, std::vector<Double_t> xp
{
	t = tp;
	x = xp;
	nRuns = nRunsp;
	
	nThreads =  nThreads_;

	myAnalyse = new Analyse();
	myAnalyse -> AnalyseGaus(t,x);

	myLattice = new Lattice();
	
	myLattice -> SetNop(nop);
	myLattice -> SetPercent(percent*100);
	myLattice -> SetLattice(myAnalyse -> GetMu(), myAnalyse -> GetSigma());
	
	canvasB = new TCanvas("draw2Dcanv", "Lattice",800,400);
	canvasB -> Divide(2,1);
	
	canvasB2 = new TCanvas("draw2Dcanv2", "Lattice2",800,400);
	
	BM1D_histo = new TH2D("BM1D_histo", "BM1D_histo", myLattice -> GetWidth() , myLattice -> GetMuMin(), (myLattice -> GetMuMax()) , myLattice -> GetHeight() ,  myLattice -> GetSigmaMin(),  (myLattice -> GetSigmaMax()) );
	BM1D_histo2 = new TH2D("BM1D_histo2", "BM1D_histo2",  myLattice -> GetWidth() , myLattice -> GetMuMin(), (myLattice -> GetMuMax()) , myLattice -> GetHeight() ,  myLattice -> GetSigmaMin(),  (myLattice -> GetSigmaMax()) );
    
	graphArray.size = myLattice -> GetLatticeSize();
	graphArray.X    = new double[graphArray.size] {};
	graphArray.Y    = new double[graphArray.size] {};
	
	gr = new TGraph(graphArray.size);
	
	delete myAnalyse;
}

Draw2D::~Draw2D()
{
	canvasB->Clear();
	canvasB->Closed();
	delete canvasB;
	delete BM1D_histo;
	delete BM1D_histo2;
    
	canvasB2->Clear();
	canvasB2->Closed();
	delete canvasB2;
	delete gr;
	
	delete myLattice;
	 
	delete[] graphArray.X;
	delete[] graphArray.Y;
}



void Draw2D::Histo2D()
{
	std::cout << "maxSigma:" <<  myLattice -> GetSigmaMax() << std::endl;
	std::cout << "maxMu:" <<   myLattice -> GetMuMax() << std::endl;
	std::cout << "minSigma:" <<  myLattice -> GetSigmaMin() << std::endl;
	std::cout << "minMu:" <<   myLattice -> GetMuMin() << std::endl;
	
	
	pthread_t thread[nThreads];
	Draw2DWorkerThread *worker[nThreads];
	
    pthread_attr_t attr;
	
	pthread_mutex_t histoMutex;
	pthread_mutex_init(&histoMutex, NULL);
    int rc;

    void *status;
	
	int jobSize = myLattice -> GetLatticeSize();
	if(nThreads <= 0 || jobSize <= 0)
	{
		 std::cout<<"nThreads >= 1!!"<<std::endl;
		 exit(-1);
	}
	
	if(jobSize <= nThreads || nThreads > 32)    //small jobb size or too large nThreads? -> run single thread mode
	{
		std::cout<<"strange jobSize or nThread number!! run single thread mode!!"<<std::endl;
		worker[0] = new Draw2DWorkerThread(0, jobSize, x, t, nRuns, myLattice, BM1D_histo, BM1D_histo2, graphArray, &histoMutex);
		nThreads = 1;
	}
	else  //normal multi thread run
	{
		std::cout<<"Crusher run on "<< nThreads <<"thread"<<std::endl;
		int jobSliceSize = jobSize / nThreads;
	
		for(int i=0; i<nThreads; i++)
		{
			if(i == (nThreads - 1))  //larger slice
			{
				worker[i] = new Draw2DWorkerThread(jobSliceSize * i, (jobSize - (jobSliceSize * i)), x, t, nRuns, myLattice, BM1D_histo, BM1D_histo2, graphArray, &histoMutex);
			}
			else // normal slices
			{
				worker[i] = new Draw2DWorkerThread(jobSliceSize * i, jobSliceSize, x, t, nRuns, myLattice, BM1D_histo, BM1D_histo2, graphArray, &histoMutex);
			}
		}
	}
	
	
    pthread_attr_init(&attr);
    pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);

    for(int i=0; i<nThreads; i++)
	{
       std::cout<<"creating thread:"<<i<<std::endl;
       rc = pthread_create(&thread[i], &attr, (THREADFUNCPTR) &Draw2DWorkerThread::WorkerFunction, (void *)worker[i]);  
       if (rc) 
	   {
          std::cout<<"ERROR; pthread:"<<i<<"create failed!"<<std::endl;
		  exit(-1);
       }
    }
	
    pthread_attr_destroy(&attr);
	
    for(int i=0; i<nThreads; i++)
	{
       rc = pthread_join(thread[i], &status);
       if (rc) 
	   {
          std::cout<<"ERROR; pthread:"<<i<<"join failed!"<<std::endl;
          exit(-1);
       }
	}
	
	for(int i=0; i<nThreads; i++)
	{
		delete worker[i];
	}
	
	std::cout << "RunMachine done" << std::endl;
		
		
	gr -> SetMarkerColor(46);	
	canvasB2 -> cd();
	gr -> DrawGraph(graphArray.size, graphArray.X, graphArray.Y, "AP*");

	BM1D_histo -> SetMarkerStyle(kFullCircle);
	BM1D_histo-> SetMarkerStyle(21);
	canvasB -> cd(1);
	BM1D_histo -> Draw("PLC PMC");
	
	canvasB -> cd(2);	
	BM1D_histo2 -> Draw("COLZ");

	std::cout << "Histo draw done" << std::endl;
}

