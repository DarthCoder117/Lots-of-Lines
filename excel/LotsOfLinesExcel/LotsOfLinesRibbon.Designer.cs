namespace LotsOfLinesExcel
{
    partial class LotsOfLinesRibbon : Microsoft.Office.Tools.Ribbon.RibbonBase
    {
        /// <summary>
        /// Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        public LotsOfLinesRibbon()
            : base(Globals.Factory.GetRibbonFactory())
        {
            InitializeComponent();
        }

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

        #region Component Designer generated code

        /// <summary>
        /// Required method for Designer support - do not modify
        /// the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            this.lotsOfLinesTab = this.Factory.CreateRibbonTab();
            this.lotsOfLinesGroup = this.Factory.CreateRibbonGroup();
            this.openInLotsOfLinesButton = this.Factory.CreateRibbonButton();
            this.lotsOfLinesTab.SuspendLayout();
            this.lotsOfLinesGroup.SuspendLayout();
            this.SuspendLayout();
            // 
            // lotsOfLinesTab
            // 
            this.lotsOfLinesTab.Groups.Add(this.lotsOfLinesGroup);
            this.lotsOfLinesTab.Label = "Lots Of Lines";
            this.lotsOfLinesTab.Name = "lotsOfLinesTab";
            // 
            // lotsOfLinesGroup
            // 
            this.lotsOfLinesGroup.Items.Add(this.openInLotsOfLinesButton);
            this.lotsOfLinesGroup.Label = "Lots Of Lines";
            this.lotsOfLinesGroup.Name = "lotsOfLinesGroup";
            // 
            // openInLotsOfLinesButton
            // 
            this.openInLotsOfLinesButton.ControlSize = Microsoft.Office.Core.RibbonControlSize.RibbonControlSizeLarge;
            this.openInLotsOfLinesButton.Label = "Open In Lots of Lines";
            this.openInLotsOfLinesButton.Name = "openInLotsOfLinesButton";
            this.openInLotsOfLinesButton.ShowImage = true;
            // 
            // LotsOfLinesRibbon
            // 
            this.Name = "LotsOfLinesRibbon";
            this.RibbonType = "Microsoft.Excel.Workbook";
            this.Tabs.Add(this.lotsOfLinesTab);
            this.Load += new Microsoft.Office.Tools.Ribbon.RibbonUIEventHandler(this.LotsOfLinesRibbon_Load);
            this.lotsOfLinesTab.ResumeLayout(false);
            this.lotsOfLinesTab.PerformLayout();
            this.lotsOfLinesGroup.ResumeLayout(false);
            this.lotsOfLinesGroup.PerformLayout();
            this.ResumeLayout(false);

        }

        #endregion

        internal Microsoft.Office.Tools.Ribbon.RibbonTab lotsOfLinesTab;
        internal Microsoft.Office.Tools.Ribbon.RibbonGroup lotsOfLinesGroup;
        internal Microsoft.Office.Tools.Ribbon.RibbonButton openInLotsOfLinesButton;
    }

    partial class ThisRibbonCollection
    {
        internal LotsOfLinesRibbon LotsOfLinesRibbon
        {
            get { return this.GetRibbon<LotsOfLinesRibbon>(); }
        }
    }
}
