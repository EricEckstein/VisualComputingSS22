using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;

namespace FirstOpenCLProgram
{
    public partial class Form1 : Form
    {
        public Form1()
        {
            InitializeComponent();
        }


        private void btnOpenCL_Click(object sender, EventArgs e)
        {
            string vecSum = @"
                     __kernel void
                    floatVectorSum(__global       float * v1,
                                   __global       float * v2)
                    {
                        // Vector element index
                        int i = get_global_id(0);
                        v1[i] = v1[i] + v2[i];
                    }";

            //Initializes OpenCL Platforms and Devices and sets everything up
            OpenCLTemplate.CLCalc.InitCL();

            //Compiles the source codes. The source is a string array because the user may want
            //to split the source into many strings.
            OpenCLTemplate.CLCalc.Program.Compile(new string[] { vecSum });

            //Gets host access to the OpenCL floatVectorSum kernel
            OpenCLTemplate.CLCalc.Program.Kernel VectorSum = new OpenCLTemplate.CLCalc.Program.Kernel("floatVectorSum");

            //We want to sum 2000 numbers
            int n = 2000;

            //Create vectors with 2000 numbers
            float[] v1 = new float[n], v2=new float[n];

            //Creates population for v1 and v2
            for (int i = 0; i < n; i++)
            {
                v1[i] = (float)i / 10;
                v2[i] = -(float)i / 9;
            }

            
            //Creates vectors v1 and v2 in the device memory
            OpenCLTemplate.CLCalc.Program.Variable varV1 = new OpenCLTemplate.CLCalc.Program.Variable(v1);
            OpenCLTemplate.CLCalc.Program.Variable varV2 = new OpenCLTemplate.CLCalc.Program.Variable(v2);

            //Arguments of VectorSum kernel
            OpenCLTemplate.CLCalc.Program.Variable[] args = new OpenCLTemplate.CLCalc.Program.Variable[] { varV1, varV2 };
            
            //How many workers will there be? We need "n", one for each element
            int[] workers = new int[1] { n };

            //Execute the kernel
            VectorSum.Execute(args, workers);

            //Read device memory varV1 to host memory v1
            varV1.ReadFromDeviceTo(v1);

        }

        private void Form1_Load(object sender, EventArgs e)
        {
            //Initializes OpenCL
            OpenCLTemplate.CLCalc.InitCL();

            //Creates two int arrays of the same size.
            //OpenCLTemplate checks these sizes
            float[] myArray = new float[10];
            float[] myArray2 = new float[10];

            //Creates some data to myArray
            for (int i = 0; i < myArray.Length; i++)
                myArray[i] = (float)i / 7;

            //Allocates memory in the OpenCL device
            OpenCLTemplate.CLCalc.Program.Variable varMyArray = 
                new OpenCLTemplate.CLCalc.Program.Variable(myArray);

            //Reads from device memory to myArray2
            varMyArray.ReadFromDeviceTo(myArray2);

            //Breakpoint here and notice here that myArray2 
            //and myArray are different.
            //This is because we set AutoWriteToDevice 
            //to false. We need to copy the data manually
            varMyArray.WriteToDevice(myArray);
            varMyArray.ReadFromDeviceTo(myArray2);

            //Now it's there.
        }
    }
}
