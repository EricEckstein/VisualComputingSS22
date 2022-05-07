namespace FirstOpenCLProgram
{
    partial class Form1
    {
        /// <summary>
        /// Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// Clean up any resources being used.
        /// </summary>
        /// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows Form Designer generated code

        /// <summary>
        /// Required method for Designer support - do not modify
        /// the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            this.btnOpenCL = new System.Windows.Forms.Button();
            this.SuspendLayout();
            // 
            // btnOpenCL
            // 
            this.btnOpenCL.Location = new System.Drawing.Point(12, 12);
            this.btnOpenCL.Name = "btnOpenCL";
            this.btnOpenCL.Size = new System.Drawing.Size(75, 23);
            this.btnOpenCL.TabIndex = 0;
            this.btnOpenCL.Text = "OpenCL";
            this.btnOpenCL.UseVisualStyleBackColor = true;
            this.btnOpenCL.Click += new System.EventHandler(this.btnOpenCL_Click);
            // 
            // Form1
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(284, 262);
            this.Controls.Add(this.btnOpenCL);
            this.Name = "Form1";
            this.Text = "First OpenCL Program";
            this.Load += new System.EventHandler(this.Form1_Load);
            this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.Button btnOpenCL;
    }
}

