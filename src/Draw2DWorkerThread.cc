#include "Draw2DWorkerThread.hh"

Draw2DWorkerThread::Draw2DWorkerThread(int jobOffset_, int jobSize_, std::vector<Double_t> x_, std::vector<Double_t> t_, int nRuns_, Lattice *myLattice_, TH2D *BM1D_histo_, TH2D *BM1D_histo2_, struct graphArray graphArray_, pthread_mutex_t *histoMutex_)
{
	std::cout << "Draw2DWorkerThread::Draw2DWorkerThread" <<std::endl;
	//copy to private variables
	x = x_;
	t = t_;
	
	myLattice = myLattice_;
	
	BM1D_histo  = BM1D_histo_;
	BM1D_histo2 =BM1D_histo2_;
	graphArray = graphArray_;
	
	nRuns = nRuns_;
	
	histoMutex = histoMutex_;
	
	jobOffset = jobOffset_;
	jobSize = jobSize_;
	
	//create Crusher instance
	myCrusher = new Crusher(t,x);
	
	//calculate lattice parameters  TODO rework lattice class!!
	XbinSize = (myLattice -> GetMuMax() - myLattice -> GetMuMin())/ myLattice -> GetWidth() ;
	YbinSize =( myLattice -> GetSigmaMax() -  myLattice -> GetSigmaMin() ) / myLattice -> GetHeight();
	XbinSizePer2  	= XbinSize/2;
	YbinSizePer2  	= YbinSize/2;
	latticeHeight 	= myLattice -> GetHeight();
	latticeWidth 	= myLattice -> GetWidth();
	latticeMuMin 	= myLattice -> GetMuMin();
	latticeSigmaMin	= myLattice -> GetSigmaMin();
}


Draw2DWorkerThread::~Draw2DWorkerThread()
{
	delete myCrusher;
}


void Draw2DWorkerThread::WorkerFunction()
{
	std::cout << "Draw2DWorkerThread::WorkerFunction" <<std::endl;
	std::cout << "jobOffset:"<< jobOffset<< "jobSize:"  << jobSize <<std::endl;
	for(int i = jobOffset; i < (jobOffset + jobSize); i++) 
		{
			std::cout<<"progress: "<<i<<"/"<<myLattice -> GetLatticeSize()<<"point\n";
			
			if(myCrusher -> RunMachine(nRuns, myLattice -> GetMuSigma(i)))
				{
				    pthread_mutex_lock (histoMutex);  //fill histo thread safe???
    
					BM1D_histo  ->Fill((i / latticeHeight) * XbinSize + XbinSizePer2 + latticeMuMin, (i % latticeHeight) * YbinSize + YbinSizePer2 + latticeSigmaMin );
					BM1D_histo2 ->Fill((i / latticeHeight) * XbinSize + XbinSizePer2 + latticeMuMin, (i % latticeHeight) * YbinSize + YbinSizePer2 + latticeSigmaMin );
					
					graphArray.X[i] = (i / latticeHeight) * XbinSize;
					graphArray.Y[i] = (i %  latticeHeight)* YbinSize;
					
					pthread_mutex_unlock (histoMutex);
						
				}
		}		
 pthread_exit((void*) 0);  //kell?? vagy NULL??	
}