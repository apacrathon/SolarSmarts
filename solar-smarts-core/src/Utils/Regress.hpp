#pragma once

extern "C" {
	SS_INLINE extern bool __cdecl RegressInitializeWithHandlers(mclOutputHandlerFcn error_handler, mclOutputHandlerFcn print_handler);
	SS_INLINE extern bool __cdecl RegressInitialize(void);
	SS_INLINE extern void __cdecl RegressTerminate(void);
	SS_INLINE extern void __cdecl RegressPrintStackTrace(void);
	SS_INLINE bool __cdecl mlxRegress(int nlhs, mxArray *plhs[], int nrhs, mxArray *prhs[]);
}

SS_INLINE extern  __declspec(dllimport) void __cdecl Regress(const mwArray& input, const mwArray& output);

namespace SolarSmarts
{
	namespace Utils
	{
		class Regression
		{
		public:
			SS_INLINE Regression() 
			{
				m_output = std::make_shared<mwArray>();
			}
			
			int run_main(int argc, const char **argv)
			{
				if (!m_inputValid)
				{
					PRINT("The input has not been set.");
					return -1;
				}

				// set up the state for the MCR instance
				if (!mclInitializeApplication(NULL, 0))
				{
					PRINT("Could not initialize the application properly.");
					return -1;
				}

				// load MATLAB code into MCR
				if (!RegressInitialize())
				{
					PRINT("could not initialize the library properly.");
					return -1;
				}

				try
				{
					Regress(*this->m_input, *this->m_output);	// run matlab func
				}
				catch (const mwException& e)
				{
					PRINT("%s", e.what());
					return -2;
				}
				catch (...)
				{
					PRINT("Encountered an unexpected error.");
					return -3;
				}

				RegressTerminate(); // release resources used by MATLAB code
				return mclTerminateApplication(); // release all resources used by the MCR
			}
			
			SS_INLINE void SetInput(mwArray input)
			{
				m_input = std::make_shared<mwArray>(input);
				if (!input.IsEmpty()) m_inputValid = true;
			}
			
			SS_INLINE mwArray GetOutput()
			{
				return *m_output;
			}
		private:
			std::shared_ptr<mwArray> m_input;
			std::shared_ptr<mwArray> m_output;
			bool m_inputValid = false;
		};
	}
}