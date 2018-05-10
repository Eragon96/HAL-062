namespace KNRapp
{
    partial class FormManipulator
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
            this.speedTrackBar1 = new System.Windows.Forms.TrackBar();
            this.speedModuleTrackBar = new System.Windows.Forms.TrackBar();
            this.STOP = new System.Windows.Forms.Button();
            this.START = new System.Windows.Forms.Button();
            this.speedModuleTextBox = new System.Windows.Forms.TextBox();
            this.position1TextBox = new System.Windows.Forms.TextBox();
            this.position2TextBox = new System.Windows.Forms.TextBox();
            this.position3TextBox = new System.Windows.Forms.TextBox();
            this.position4TextBox = new System.Windows.Forms.TextBox();
            this.position5TextBox = new System.Windows.Forms.TextBox();
            this.position6TextBox = new System.Windows.Forms.TextBox();
            this.position7TextBox = new System.Windows.Forms.TextBox();
            this.textBox9 = new System.Windows.Forms.TextBox();
            this.textBox10 = new System.Windows.Forms.TextBox();
            this.textBox11 = new System.Windows.Forms.TextBox();
            this.textBox12 = new System.Windows.Forms.TextBox();
            this.textBox13 = new System.Windows.Forms.TextBox();
            this.textBox14 = new System.Windows.Forms.TextBox();
            this.textBox15 = new System.Windows.Forms.TextBox();
            this.textBox1 = new System.Windows.Forms.TextBox();
            this.changeButton = new System.Windows.Forms.Button();
            this.kinematicsTextBox = new System.Windows.Forms.TextBox();
            ((System.ComponentModel.ISupportInitialize)(this.speedTrackBar1)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.speedModuleTrackBar)).BeginInit();
            this.SuspendLayout();
            // 
            // speedTrackBar1
            // 
            this.speedTrackBar1.Location = new System.Drawing.Point(8, 8);
            this.speedTrackBar1.Name = "speedTrackBar1";
            this.speedTrackBar1.Size = new System.Drawing.Size(224, 45);
            this.speedTrackBar1.TabIndex = 0;
            // 
            // speedModuleTrackBar
            // 
            this.speedModuleTrackBar.Location = new System.Drawing.Point(12, 12);
            this.speedModuleTrackBar.Maximum = 100;
            this.speedModuleTrackBar.Name = "speedModuleTrackBar";
            this.speedModuleTrackBar.Size = new System.Drawing.Size(452, 45);
            this.speedModuleTrackBar.TabIndex = 0;
            this.speedModuleTrackBar.Value = 10;
            this.speedModuleTrackBar.Scroll += new System.EventHandler(this.trackBar1_Scroll);
            // 
            // STOP
            // 
            this.STOP.Font = new System.Drawing.Font("Microsoft Sans Serif", 7F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.STOP.ForeColor = System.Drawing.Color.Red;
            this.STOP.Location = new System.Drawing.Point(440, 119);
            this.STOP.Name = "STOP";
            this.STOP.Size = new System.Drawing.Size(55, 55);
            this.STOP.TabIndex = 1;
            this.STOP.Text = "STOP";
            this.STOP.UseVisualStyleBackColor = true;
            this.STOP.Click += new System.EventHandler(this.STOP_Click);
            // 
            // START
            // 
            this.START.Font = new System.Drawing.Font("Microsoft Sans Serif", 7F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.START.ForeColor = System.Drawing.Color.Green;
            this.START.Location = new System.Drawing.Point(440, 58);
            this.START.Name = "START";
            this.START.Size = new System.Drawing.Size(55, 55);
            this.START.TabIndex = 2;
            this.START.Text = "START";
            this.START.UseVisualStyleBackColor = true;
            this.START.Click += new System.EventHandler(this.START_Click);
            // 
            // speedModuleTextBox
            // 
            this.speedModuleTextBox.Location = new System.Drawing.Point(470, 21);
            this.speedModuleTextBox.Name = "speedModuleTextBox";
            this.speedModuleTextBox.Size = new System.Drawing.Size(25, 20);
            this.speedModuleTextBox.TabIndex = 3;
            this.speedModuleTextBox.Text = "10";
            this.speedModuleTextBox.TextAlign = System.Windows.Forms.HorizontalAlignment.Center;
            this.speedModuleTextBox.TextChanged += new System.EventHandler(this.speedModuleTextBox_TextChanged);
            // 
            // position1TextBox
            // 
            this.position1TextBox.Location = new System.Drawing.Point(12, 58);
            this.position1TextBox.Name = "position1TextBox";
            this.position1TextBox.Size = new System.Drawing.Size(56, 20);
            this.position1TextBox.TabIndex = 4;
            this.position1TextBox.TextAlign = System.Windows.Forms.HorizontalAlignment.Center;
            // 
            // position2TextBox
            // 
            this.position2TextBox.Location = new System.Drawing.Point(13, 85);
            this.position2TextBox.Name = "position2TextBox";
            this.position2TextBox.Size = new System.Drawing.Size(55, 20);
            this.position2TextBox.TabIndex = 5;
            this.position2TextBox.TextAlign = System.Windows.Forms.HorizontalAlignment.Center;
            // 
            // position3TextBox
            // 
            this.position3TextBox.Location = new System.Drawing.Point(12, 111);
            this.position3TextBox.Name = "position3TextBox";
            this.position3TextBox.Size = new System.Drawing.Size(55, 20);
            this.position3TextBox.TabIndex = 6;
            this.position3TextBox.TextAlign = System.Windows.Forms.HorizontalAlignment.Center;
            // 
            // position4TextBox
            // 
            this.position4TextBox.Location = new System.Drawing.Point(13, 137);
            this.position4TextBox.Name = "position4TextBox";
            this.position4TextBox.Size = new System.Drawing.Size(55, 20);
            this.position4TextBox.TabIndex = 7;
            this.position4TextBox.TextAlign = System.Windows.Forms.HorizontalAlignment.Center;
            // 
            // position5TextBox
            // 
            this.position5TextBox.Location = new System.Drawing.Point(12, 163);
            this.position5TextBox.Name = "position5TextBox";
            this.position5TextBox.Size = new System.Drawing.Size(55, 20);
            this.position5TextBox.TabIndex = 8;
            this.position5TextBox.TextAlign = System.Windows.Forms.HorizontalAlignment.Center;
            // 
            // position6TextBox
            // 
            this.position6TextBox.Location = new System.Drawing.Point(13, 189);
            this.position6TextBox.Name = "position6TextBox";
            this.position6TextBox.Size = new System.Drawing.Size(55, 20);
            this.position6TextBox.TabIndex = 9;
            this.position6TextBox.TextAlign = System.Windows.Forms.HorizontalAlignment.Center;
            // 
            // position7TextBox
            // 
            this.position7TextBox.Location = new System.Drawing.Point(13, 215);
            this.position7TextBox.Name = "position7TextBox";
            this.position7TextBox.Size = new System.Drawing.Size(55, 20);
            this.position7TextBox.TabIndex = 10;
            this.position7TextBox.TextAlign = System.Windows.Forms.HorizontalAlignment.Center;
            // 
            // textBox9
            // 
            this.textBox9.Location = new System.Drawing.Point(75, 215);
            this.textBox9.Name = "textBox9";
            this.textBox9.Size = new System.Drawing.Size(55, 20);
            this.textBox9.TabIndex = 17;
            this.textBox9.TextAlign = System.Windows.Forms.HorizontalAlignment.Center;
            // 
            // textBox10
            // 
            this.textBox10.Location = new System.Drawing.Point(75, 189);
            this.textBox10.Name = "textBox10";
            this.textBox10.Size = new System.Drawing.Size(55, 20);
            this.textBox10.TabIndex = 16;
            this.textBox10.TextAlign = System.Windows.Forms.HorizontalAlignment.Center;
            // 
            // textBox11
            // 
            this.textBox11.Location = new System.Drawing.Point(74, 163);
            this.textBox11.Name = "textBox11";
            this.textBox11.Size = new System.Drawing.Size(55, 20);
            this.textBox11.TabIndex = 15;
            this.textBox11.TextAlign = System.Windows.Forms.HorizontalAlignment.Center;
            // 
            // textBox12
            // 
            this.textBox12.Location = new System.Drawing.Point(75, 137);
            this.textBox12.Name = "textBox12";
            this.textBox12.Size = new System.Drawing.Size(55, 20);
            this.textBox12.TabIndex = 14;
            this.textBox12.TextAlign = System.Windows.Forms.HorizontalAlignment.Center;
            // 
            // textBox13
            // 
            this.textBox13.Location = new System.Drawing.Point(74, 111);
            this.textBox13.Name = "textBox13";
            this.textBox13.Size = new System.Drawing.Size(55, 20);
            this.textBox13.TabIndex = 13;
            this.textBox13.TextAlign = System.Windows.Forms.HorizontalAlignment.Center;
            // 
            // textBox14
            // 
            this.textBox14.Location = new System.Drawing.Point(75, 85);
            this.textBox14.Name = "textBox14";
            this.textBox14.Size = new System.Drawing.Size(55, 20);
            this.textBox14.TabIndex = 12;
            this.textBox14.TextAlign = System.Windows.Forms.HorizontalAlignment.Center;
            // 
            // textBox15
            // 
            this.textBox15.Location = new System.Drawing.Point(74, 58);
            this.textBox15.Name = "textBox15";
            this.textBox15.Size = new System.Drawing.Size(56, 20);
            this.textBox15.TabIndex = 11;
            this.textBox15.TextAlign = System.Windows.Forms.HorizontalAlignment.Center;
            // 
            // textBox1
            // 
            this.textBox1.Location = new System.Drawing.Point(188, 119);
            this.textBox1.Name = "textBox1";
            this.textBox1.Size = new System.Drawing.Size(182, 20);
            this.textBox1.TabIndex = 18;
            // 
            // changeButton
            // 
            this.changeButton.Location = new System.Drawing.Point(13, 242);
            this.changeButton.Name = "changeButton";
            this.changeButton.Size = new System.Drawing.Size(55, 23);
            this.changeButton.TabIndex = 19;
            this.changeButton.Text = "Change";
            this.changeButton.UseVisualStyleBackColor = true;
            this.changeButton.Click += new System.EventHandler(this.changeButton_Click);
            // 
            // kinematicsTextBox
            // 
            this.kinematicsTextBox.Location = new System.Drawing.Point(75, 244);
            this.kinematicsTextBox.Name = "kinematicsTextBox";
            this.kinematicsTextBox.Size = new System.Drawing.Size(126, 20);
            this.kinematicsTextBox.TabIndex = 20;
            this.kinematicsTextBox.Text = "Inverse Kinematics: false";
            this.kinematicsTextBox.TextAlign = System.Windows.Forms.HorizontalAlignment.Center;
            // 
            // FormManipulator
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(507, 271);
            this.Controls.Add(this.kinematicsTextBox);
            this.Controls.Add(this.changeButton);
            this.Controls.Add(this.textBox1);
            this.Controls.Add(this.textBox9);
            this.Controls.Add(this.textBox10);
            this.Controls.Add(this.textBox11);
            this.Controls.Add(this.textBox12);
            this.Controls.Add(this.textBox13);
            this.Controls.Add(this.textBox14);
            this.Controls.Add(this.textBox15);
            this.Controls.Add(this.position7TextBox);
            this.Controls.Add(this.position6TextBox);
            this.Controls.Add(this.position5TextBox);
            this.Controls.Add(this.position4TextBox);
            this.Controls.Add(this.position3TextBox);
            this.Controls.Add(this.position2TextBox);
            this.Controls.Add(this.position1TextBox);
            this.Controls.Add(this.speedModuleTextBox);
            this.Controls.Add(this.START);
            this.Controls.Add(this.STOP);
            this.Controls.Add(this.speedModuleTrackBar);
            this.Name = "FormManipulator";
            this.Text = "Manipulator";
            this.Load += new System.EventHandler(this.FormManipulator_Load);
            ((System.ComponentModel.ISupportInitialize)(this.speedTrackBar1)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.speedModuleTrackBar)).EndInit();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion
        private System.Windows.Forms.TrackBar speedTrackBar1;
        private System.Windows.Forms.TrackBar speedModuleTrackBar;
        private System.Windows.Forms.Button STOP;
        private System.Windows.Forms.Button START;
        private System.Windows.Forms.TextBox speedModuleTextBox;
        private System.Windows.Forms.TextBox position1TextBox;
        private System.Windows.Forms.TextBox position2TextBox;
        private System.Windows.Forms.TextBox position3TextBox;
        private System.Windows.Forms.TextBox position4TextBox;
        private System.Windows.Forms.TextBox position5TextBox;
        private System.Windows.Forms.TextBox position6TextBox;
        private System.Windows.Forms.TextBox position7TextBox;
        private System.Windows.Forms.TextBox textBox9;
        private System.Windows.Forms.TextBox textBox10;
        private System.Windows.Forms.TextBox textBox11;
        private System.Windows.Forms.TextBox textBox12;
        private System.Windows.Forms.TextBox textBox13;
        private System.Windows.Forms.TextBox textBox14;
        private System.Windows.Forms.TextBox textBox15;
        private System.Windows.Forms.TextBox textBox1;
        private System.Windows.Forms.Button changeButton;
        private System.Windows.Forms.TextBox kinematicsTextBox;
    }
}